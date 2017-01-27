#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include <stdlib.h>

#include <inttypes.h>
#include "tinythread.h"

using namespace std;
using namespace tthread;

#define RECSINMEM 100000

int numThreads=4;
bool done=0;

string MEM[ RECSINMEM ];
string OTHERMEM[ RECSINMEM ];
string *records;


mutex workerLock; // used for mutual exclusion of workersWorking
unsigned workersWorking=0;
mutex producerLock;




void 
workerThread(void *arg) {
  
  int i;
  int id =  *((int*)arg ); // thread id

 top:
  // spin loop... wait for the producer to generate some data
  while (workersWorking == 0) 
    ;


  for (i=0; i < RECSINMEM; ++i) {
    if (i % numThreads == id) { 
      if (records[i].empty())
	continue;
      // do work HERE
      //      cout << records[i] << endl;
    }
  }


  if (done)
    return;

  workerLock.lock();
  --workersWorking;
  // last worker to check in
  if (workersWorking == 0)
    producerLock.unlock(); // wake up the producer
  workerLock.unlock();
  
  goto top;

}



bool
buffer(istream &in, string mem[]) {

  unsigned i=0;
  string dummy;

  while (getline(in, mem[i])) {
    getline(in, mem[i]); // read in the DNA string

    getline(in, dummy); // the +
    getline(in, dummy); // the quality string (ignored)
    ++i;
    if (i == RECSINMEM) {
      int c = in.peek();
      if (c == EOF)
	return 1;
      return 0;
    }
  }

  for ( ; i < RECSINMEM; ++i)
    mem[i].clear();

  return 1;
}



void 
mainThread(void *arg) {
  unsigned i=1;


  bool fileDone=buffer(std::cin, MEM); // read in a bunch of data
  records = MEM; // set up the pointer

  workersWorking= numThreads; // let the workers start processing the data

  while (! fileDone) {
    ++i;
    if (i % 2 == 0) 
      fileDone=buffer(std::cin, OTHERMEM);
    else 
      fileDone=buffer(std::cin, MEM);


    producerLock.lock(); // wait for the workers to finish

    if (i % 2 == 0) // swap the buffers
      records = OTHERMEM;
    else
      records = MEM;

    // wake up the workers
    workersWorking= numThreads;
    
  }
  // we're done reading in the data
  done=1;
  

}



int
main(int argc, char** argv) {
  
  int i;
  thread *t;
  list<thread *> threads;
  int *ids = new int [ numThreads] ;

  std::ios::sync_with_stdio(false);

  workerLock.unlock();
  producerLock.unlock();


  t = new thread(mainThread, NULL);
  threads.push_back(t);


  for (i=0;  i < numThreads; ++i) {
    ids[i] = i;
    t = new thread(workerThread, (void*) &(ids[i]) );
    threads.push_back(t);
  }

  for (list<thread*>::iterator itr = threads.begin(); itr != threads.end(); ++itr) {
    t = *itr;
    t->join();
    delete t;
  }


  delete ids;
  return 0;
}
