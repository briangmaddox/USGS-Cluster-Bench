/***************************************************************************
                          ServerBenchMaster.cpp  -  description
                             -------------------
    begin                : Tue Jul 3 2001
    copyright            : (C) 2001 by 
    email                : cbilder@mcpc1159
 ***************************************************************************/

/***************************************************************************
 * This software is free under the terms of the MPL (Mozilla Public License*
 * See www.mozilla.org for details.                                        *
 ***************************************************************************/

#include "ServerBenchMaster.h"
#include <sstream>

using namespace USGSBenchmark;

//****************************************************************************
ServerBenchMaster::ServerBenchMaster() : PvmBenchmark(SERVERBENCHMASTERTAG),
      childtid(0),
      num_runs(0),
      explicit_names(false),
      number_slaves(0),
      data_size(0)

{}

//****************************************************************************
ServerBenchMaster::~ServerBenchMaster()
{
  if (childtid)
    delete childtid;

}

//****************************************************************************
bool ServerBenchMaster::run() throw(BenchmarkException)
{
  int  bufferid(0), len(0), tag(0),    //pvm tags
    temptid(0);
  Time_stat timest;                    //temporary time file
  int counter(0);
  std::list<Time_stat> timelist;       //list of time entries
  char * buffer(0);                    //tempoary buffer
  long int buffer_size(0);             //buffer size




}

//****************************************************************************
void ServerBenchMaster::spawn_slaves() const throw (BenchmarkException)
{
  int counter(0);                      //counter for loops
  int numslaves(0);                    //the number of slaves actually spawned
  char * arg[2];                       //for slave argument passing

  //do some checks
  if (number_slaves <= 0)
    throw BenchmarkException
            ("ServerBenchMaster::spawn_slaves number of slaves is wrong");

  //check the childtid array
  if(childtid)
  {
    delete [] childtid;
    childtid = NULL;
  }

  //create the childtid array
  if(!(childtid = new (std::nothrow) int[number_slaves]))
    throw BenchmarkException
            ("ServerBenchMaster::run-unable to create childtid array");

  if (explicit_names)
  {
    if (name_table.size() != static_cast<unsigned int>(number_slaves))
      throw BenchmarkException
              ("ServerBenchMaster::spawn_slaves name_table is bad");

    for(counter = 0; counter < number_slaves; ++counter)
    {
      arg[0] = slave_config.c_str();
      arg[1] = 0;

      //do a spawning loop
      numslaves = pvm_spawn(slave_exe.c_str(), arg, PvmTaskHost,
                            name_table[counter].c_str(), 1,
                            &(childtid[counter]));
      if (numbslaves != 1)
      {
        delete [] childtid;
        childtid = 0;
        throw BenchmarkException
                ("ServerBenchMaster::spawn_slaves unable to spawn explicit");
      }
    }
  }
  else
  {
    //just spawn a bunch of slaves
    numslaves = pvm_spawn("cluster_bench", arg, PvmTaskDefault,
                          0, number_slaves, childtid);
    if (numslaves != number_slaves)
    {
      delete [] childtid;
      childtid = 0;
      throw BenchmarkException
              ("ServerBenchMaster::spawn_slaves unable to spawn");
    }
  }
}






