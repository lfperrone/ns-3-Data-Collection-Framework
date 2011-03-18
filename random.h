/*
 * random.h : this file was extracted from DaSSF
 */

/*
 * Copyright (c) 1998-2002 Dartmouth College
 *
 * Permission is hereby granted, free of charge, to any individual or 
 * institution obtaining a copy of this software and associated 
 * documentation files (the "Software"), to use, copy, modify, and 
 * distribute without restriction, provided that this copyright and 
 * permission notice is maintained, intact, in all copies and supporting 
 * documentation.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL DARTMOUTH COLLEGE BE LIABLE FOR ANY CLAIM, DAMAGES 
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "rng.h"

class Random
{
public:
  enum { USE_RNG_LEHMER, USE_RNG_MT };

  /** A random stream must be part of an entity state so to make the
     simulation repeatable. Two kinds of random number generator can
     be used: Lehmer RNG, which is faster but statistically less good,
     and Mersenne Twister RNG, which although slower is proven to be
     much be better. The user can set the initial random seed; if a
     seed is not provided, the system chooses a default value.
     
  */
  Random(int _rng = USE_RNG_LEHMER, long _seed = 0);
  ~Random();

  /// Set the random seed (0 means that the system will randomly pick one)
  void set_seed(long _seed) { rng->set_seed(_seed); rng->get_random01(); }

  // Set the random seed (0 means that the system will randomly pick one)
  long get_seed() { return rng->get_seed(); }

  /// Uniform in range [0,1]
  inline double uniform() { return rng->get_random01(); }

  // Uniform in range (a,b); mean (a+b)/2, variance (b-a)*(b-a)/12
  double uniform(double a, double b);

  // range y>0, mean 1/x, variance 1/(x*x)
  double exponential(double x);

  // range y>0, mean n*x, variance n*x*x
  double erlang(long n, double x);

  // range y>=k>0, mean a*k/(a-1) a>1, variance a*k^2/((a-1)^2*(a-2)) a>2
  double pareto(double k, double a);

  // range all, mean m, variance s*s
  double normal(double m, double s);
  
  // range y>0, mean exp(a+0.5*b*b), variance (exp(b*b)-1)*exp(2*a+b*b)
  double lognormal(double a, double b);

  // range y>0, mean n, variance 2*n
   double chisquare(long n);

  // range all, mean 0 (n>1), variance n/(n - 2) (n > 2)
  double student(long n);

  /* discrete distribution */

  // range 0..1, mean p, variance p*(1-p)
  long bernoulli(double p);

  // range a..b, mean (a+b)/2, variance ((b-a+1)*(b-a+1)-1)/12
  long equilikely(long a, long b);

  // range 0..n, mean n*p, variance n*p*(1-p)
  long binomial(long n, double p);

  // range 1..., mean 1/p, variance (1-p)/(p*p)
  long geometric(double p);

  // range 1..., mean n/p, variance n*(1-p)/(p*p)
  long pascal(long n, double p);

  // range 0..., mean m, variance m
  long poisson(double m);

  /* miscellaneous functions */

  long *permute(long n); 
  void permute(long *array, long n);
  
private:
  Rng *rng;
};

#endif /*__RANDOM_H__*/
