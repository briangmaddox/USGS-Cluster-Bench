/***************************************************************************
                          PvmBenchmark.cpp  -  description
                             -------------------
    begin                : Tue Jul 17 2001
    copyright            : (C) 2001 by 
    email                : cbilder@mcpc1159
 ***************************************************************************/

/***************************************************************************
 * This software is free under the terms of the MPL (Mozilla Public License*
 * See www.mozilla.org for details.                                        *
 ***************************************************************************/

#include "PvmBenchmark.h"

using namespace USGSBenchmark;

//***************************************************************************
PvmBenchmark::PvmBenchmark(const std::string & inid) : Benchmark(inid)
{
  //enroll in pvm
  ctid = pvm_mytid();
}

//***************************************************************************
PvmBenchmark::~PvmBenchmark()
{
  //exit pvm
  pvm_exit();
}

//***************************************************************************
void PvmBenchmark::send(std::list<Time_stat> & time_list, int tid, char* data,
  long int data_size, int msgtag) throw(BenchmarkException)
{
  int sendcode(0);
  struct timeval start_time, end_time;
  struct Time_stat tm_stat;

  // get the start time
  gettimeofday(&start_time, 0);
  tm_stat.start_tm = start_time.tv_usec;

  pvm_initsend(PvmDataDefault);

  if (data_size)
    pvm_pkbyte(data, data_size, 1);

  sendcode=pvm_send(tid, msgtag);

  if(sendcode < 0)
  {
    throw BenchmarkException("Benchmark::send-Unable to send message");
  }
  else
  {
    // get the finish time
    gettimeofday(&end_time, 0);
    tm_stat.end_tm = end_time.tv_usec;
  }

  tm_stat.lapse_tm = tm_stat.end_tm - tm_stat.start_tm;

  //put it in the time_list
  time_list.push_back(tm_stat);

}

//***************************************************************************
bool
PvmBenchmark::send_recv(std::list<Time_stat> & time_list, int tid, int msgtag,
char* data, long int data_size, char* rdata, long int rdata_size )
throw(BenchmarkException)
{
  int sendcode(0);
  int  bufferid(0), len(0), tag(0),    //pvm tags
  temptid(0);
  struct timeval temp_time;
  struct Time_stat tm_stat;

  // get the start time
  gettimeofday(&temp_time, 0);
  tm_stat.start_tm = temp_time.tv_usec;

  pvm_initsend(PvmDataDefault);
  if (data_size)
    pvm_pkbyte(data, data_size, 1);
  sendcode=pvm_send(tid, msgtag);

  if(sendcode < 0)
    throw BenchmarkException("Benchmark::send_recv-Unable to send message");

  bufferid = pvm_recv(-1, -1);
  pvm_bufinfo(bufferid, &len, &tag, &temptid);

  if (tag == BENCH_QUIT || tag == BENCH_ERR)
  {
    return false;   //we are not timing any more
  }

  //check for return data
  if (rdata_size)
  {
    pvm_upkbyte(rdata, rdata_size, 1);
  }

  // get the finish time
  gettimeofday(&temp_time, 0);
  tm_stat.end_tm = temp_time.tv_usec;
  tm_stat.lapse_tm = tm_stat.end_tm - tm_stat.start_tm;

  //put it in the time_list
  time_list.push_back(tm_stat);

  return true; //got a valid timing
}
