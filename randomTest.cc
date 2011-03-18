#include <iostream>

#include "random.h"  
#include "samplestat.h"

using namespace std;

int main(int argc, char* argv[]) {

  Random myRand(Random::USE_RNG_LEHMER);
  SampleStat myStuff;
  double x;

  for (int i=0; i<100000; i++) {
    x = myRand.exponential(0.5);
    myStuff.record(x);
  }

  cout << "mean = " << myStuff.mean() << endl;
  cout << "variance = " << myStuff.variance() << endl;
}
