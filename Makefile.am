####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = cluster_bench
cluster_bench_SOURCES = PvmBenchmark.cpp SimpleDiskBench.cpp BenchmarkFactory.cpp ServerBenchSlave.cpp ServerBenchMaster.cpp Benchmark.cpp BenchmarkException.cpp main.cpp 
cluster_bench_LDADD   = ./Globals/Namespaces/libNamespaces.a 

SUBDIRS = docs Globals 

EXTRA_DIST = main.cpp BenchmarkException.cpp BenchmarkException.h Benchmark.cpp Benchmark.h ServerBenchMaster.cpp ServerBenchMaster.h ServerBenchSlave.cpp ServerBenchSlave.h MessageTags.h BenchmarkFactory.cpp BenchmarkFactory.h SimpleDiskBench.cpp SimpleDiskBench.h PvmBenchmark.cpp PvmBenchmark.h BenchmarkIO.h 

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = cluster_bench

# set the include path found by configure
INCLUDES= $(all_includes)
 
# the library search path.
cluster_bench_LDFLAGS = $(all_libraries) 
                                                                                
