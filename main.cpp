/***************************************************************************
                          main.cpp  -  main benchmarking suite entry point
                             -------------------
    begin                : Thu Jun 28 11:49:19 CDT 2001
    copyright            : (C) 2001 by 
    email                : cbilder@mcpc1159
 ***************************************************************************/

/***************************************************************************
 * This software is free under the terms of the MPL (Mozilla Public License*
 * See www.mozilla.org for details.                                        *
 ***************************************************************************/

#include <iostream>
#include <fstream>
#include "BenchmarkFactory.h"


/**
 *Simple function for ouputing the usage statement for the
 *benchmarking stuff.
 **/
void usage(char * argv[]])
{
  std::cout << "Usage: " << argv[0] << " [config file]" << std::endl;
  std::cout << "Where [config file] is the configuration file for "
            << "a given bench mark" << std::endl;
  std::cout << "If no config file is specifed the program enters interactive"
            << " mode" << std::endl;

}

/**
 *Main entry point for the benchmarking suite applications
 **/
int main(int argc, char *argv[])
{
  std::ifstream input;                  //if there is config file
  std::string tagname;                  //the type of benchmark program that
                                        //we wish to run
  Bench * bench(0);                     //the benchmarking program pointer
  BenchmarkFactory bfactory;            //factory for benchmark creation


  try
  {

    //first see if there is a config file
    if(argc > 2)
    {
     usage(argv);
     return 0;
    }

    if (argc == 2)
    {
      //try to open the output file
      input.open(argv[1]);

      if (input.fail())
      {
        throw BenchmarkException("main-Unable to open config file");
      }

      //try to read the first line
      input >> tagname;

      if (input.fail())
      {
        input.close();
        throw BenchmarkException("main-Unable to read config tag");
      }

      input.close();

      //get the benchmark and run it
      bench = bfactory.createInstance(tagname);
      bench->run();
    }
    else
    {
      //ask the user what they would like to do

    }

  }

}
