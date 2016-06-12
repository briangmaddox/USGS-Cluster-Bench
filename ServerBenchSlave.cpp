/***************************************************************************
                          ServerBenchSlave.cpp  -  description
                             -------------------
    begin                : Thu Jul 12 2001
    copyright            : (C) 2001 by 
    email                : cbilder@mcpc1159
 ***************************************************************************/

/***************************************************************************
 * This software is free under the terms of the MPL (Mozilla Public License*
 * See www.mozilla.org for details.                                        *
 ***************************************************************************/

#include "ServerBenchSlave.h"

using namespace USGSBenchmark;

//***************************************************************************
ServerBenchSlave::ServerBenchSlave() : PvmBenchmark(SERVERBENCHMASTERTAG),
mastertid(0)
{}

//***************************************************************************
ServerBenchSlave::~ServerBenchSlave()
{}


//***************************************************************************
void ServerBenchSlave::run(BenchmarkIO * inout) throw(BenchmarkException)
{
  int  bufferid(0), len(0), tag(0),    //pvm tags
  temptid(0);
  Time_stat timest;                    //temporary time file
  int counter(0);
  std::list<Time_stat> timelist;       //list of time entries
  char * buffer(0);                    //tempoary buffer
  long int buffer_size(0);             //buffer size
  bool done(false);
  timeval temptime;
  float avg(0);                        //average to give to master
  //get the parent
  mastertid = pvm_parent();

  if (mastertid == PvmNoParent)
  {
    pvm_exit();
    throw BenchmarkException
            ("ServerBenchSlave::run-Slave not spawned by master!!");
  }

  bufferid = pvm_recv(-1, -1);
  pvm_bufinfo(bufferid, &len, &tag, &temptid);

  //check the tag
  if (tag != BENCH_SETUP)
  {
    //init the buffer
    pvm_initsend(PvmDataDefault);
    //send error to the master
    pvm_send(mastertid, BENCH_ERR);
    pvm_exit();
    throw BenchmarkException
          ("ServerBenchSlave::run-Slave setup tag is wrong");
  }

  //get the buffer size
  pvm_upklong(&buffer_size, 1, 1);

  if (!buffer_size)
  {
    //init the buffer
    pvm_initsend(PvmDataDefault);
    //send the error to the master
    pvm_send(mastertid, BENCH_ERR);
    pvm_exit();
    throw BenchmarkException
          ("ServerBenchSlave::run-Slave buffer size is bad");
  }

  //create the buffer
  if (!(buf = new (std::nothrow) char [buffer_size]))
  {
    pvm_initsend(PvmDataDefault);
    pvm_send(mastertid, BENCH_ERR);
    pvm_exit();
    throw BenchmarkException
          ("ServerBenchSlave::run-Unable to create the buffer");
  }

  try
  {
    //go into the loop until
    while(!done)
    {
     //use the generic send and recv func
     done = send_recv(timelist, mastertid, BENCH_WORK, 0, 0, buf, buffer_size));
    }


    //get the average
    avg = average(timelist);

    //send it
    pvm_initsend(PvmDataDefault);
    pvm_pkfloat(&avg, 1, 1);
    pvm_send(mastertid, BENCH_WORK);

    pvm_exit();
    //delete the buffer
    delete [] buf;
  }
  catch(BenchmarkException & err)
  {
    delete [] buf;
    //send a error to the master
    pvm_initsend(PvmDataDefault);
    pvm_send(mastertid, BENCH_ERR);
    pvm_exit();
    throw err;
  }
  catch(...)
  {
    delete [] buf;
    //send a error to the master
    pvm_initsend(PvmDataDefault);
    pvm_send(mastertid, BENCH_ERR);
    pvm_exit();
    throw BenchmarkException("SeverBenchSlave::run -Unkown error");
  }
}

//***************************************************************************
void ServerBenchSlave::generateConfig(BenchmarkIO * inout)
throw(BenchmarkException)
{
  //nothing
}