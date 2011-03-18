#include <iostream>

#include "random.h"  
#include "samplestat.h"

using namespace std;

int main(int argc, char* argv[]) {

  Random myRand(Random::USE_RNG_LEHMER, 456789);
  double x;

  for (int i=0; i<10; i++) {
    x = myRand.normal(0,1);
    cout << x << endl;
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(1,1);
    cout << x << endl;
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(3,1);
    cout << x << endl;
  }
  
  for (int i=0; i<10; i++) { 
    x = myRand.normal(5,1);
    cout << x << endl;
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(6,2);
    cout << x << endl;
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(8,1);
    cout << x << endl;
  }

  for (int i=0; i<10; i++) { 
    x = myRand.normal(9,2);
    cout << x << endl;
  }

  for (int i=0; i<20; i++) { 
    x = myRand.normal(10,2);
    cout << x << endl;
  }

  for (int i=0; i<40; i++) { 
    x = myRand.normal(10,1);
    cout << x << endl;
  }

  for (int i=0; i<40; i++) { 
    x = myRand.normal(10,0.5);
    cout << x << endl;
  }

}
