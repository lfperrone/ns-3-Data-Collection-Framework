#include <iostream>

#include "random.h"  
#include "samplestat.h"

using namespace std;

int main(int argc, char* argv[]) {

  Random myRand(Random::USE_RNG_LEHMER);
  SampleStat myData;
  double x;
  vector<double> *p;

  for (int i=0; i<10; i++) {
    x = myRand.normal(0,1);
    myData.record(x);
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(1,1);
    myData.record(x);
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(3,1);
    myData.record(x);
  }
  
  for (int i=0; i<10; i++) { 
    x = myRand.normal(5,1);
    myData.record(x);
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(6,2);
    myData.record(x);
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(8,1);
    myData.record(x);
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(9,2);
    myData.record(x);
  }

  for (int i=0; i<20; i++) { 
    x = myRand.normal(10,2);
    myData.record(x);
  }

  for (int i=0; i<40; i++) { 
    x = myRand.normal(10,1);
    myData.record(x);
  }

  for (int i=0; i<40; i++) { 
    x = myRand.normal(10,0.5);
    myData.record(x);
  }

  p = myData.moving_averages(3);

  for (vector<double>::iterator i=p->begin(); i!=p->end(); ++i) {
    cout << "hello" << endl;
  }
}

