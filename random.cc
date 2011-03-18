/*
 * random.cc :- user-level random stream
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

#include <cassert>
#include <cmath>

#include "random.h"

Random::Random(int _rng, long _seed)
{
  if(_rng == USE_RNG_LEHMER) rng = new RngLehmer(_seed);
  else rng = new RngMT(_seed);
  rng->get_random01();
}

Random::~Random() { delete rng; }

double Random::uniform(double a, double b)
{
  assert(a<=b);
  if(a==b) return a;
  else return a+(b-a)*uniform();
}

double Random::exponential(double x)
{
  assert(x>0.0);
  double result = -1.0/x*log(1.0-uniform());
  return result;
}

double Random::erlang(long n, double x)
{ 
  assert(n>0 && x>0.0);
  double y = 0.0;
  for(long i = 0; i<n; i++) y += exponential(x);
  return y;
}

double Random::pareto(double k, double a)
{
  assert(k>0 && a>0);
  return k*pow(1.0-uniform(), -1.0/a);
}

double Random::normal(double m, double s)
{
  /* Uses a very accurate approximation of the normal idf due to Odeh
     & Evans, J. Applied Statistics, 1974, vol 23, pp 96-97.                      */

  assert(s>0.0);
  double p0 = 0.322232431088;        double q0 = 0.099348462606;
  double p1 = 1.0;                   double q1 = 0.588581570495;
  double p2 = 0.342242088547;        double q2 = 0.531103462366;
  double p3 = 0.204231210245e-1;     double q3 = 0.103537752850;
  double p4 = 0.453642210148e-4;     double q4 = 0.385607006340e-2;
  double u, t, p, q, z;

  u = uniform();
  if(u < 0.5) t = sqrt(-2.0*log(u));
  else t = sqrt(-2.0*log(1.0-u));
  p = p0+t*(p1+t*(p2+t*(p3+t*p4)));
  q = q0+t*(q1+t*(q2+t*(q3+t*q4)));
  if(u < 0.5) z = (p/q)-t;
  else z = t-(p/q);

  double result = m+s*z;
  return result;
}

double Random::lognormal(double a, double b)
{
  assert(b>0.0);
  double result = exp(a+b*normal(0.0, 1.0));
  return result;
}

double Random::chisquare(long n)
{ 
  assert(n>0);
  double y = 0.0;
  for(long i=0; i<n; i++) {
    double z = normal(0.0, 1.0);
    y += z*z;
  }
  return y;
}

double Random::student(long n)
{
  assert(n>0);
  double result = normal(0.0, 1.0)/sqrt(chisquare(n)/n);
  return result;
}

long Random::bernoulli(double p)
{
  assert(0.0<=p && p<=1.0);
  long result = uniform()<p ? 1 : 0;
  return result;
}

long Random::equilikely(long a, long b)
{
  assert(a<=b);
  double x = uniform();
  long v = a+(long)floor((b-a+1)*x);
  return v;
}

long Random::binomial(long n, double p)
{ 
  assert(n>0 && 0.0<p && p<1.0);
  long y = 0;
  for(long i=0; i<n; i++) y += bernoulli(p);
  return y;
}

long Random::geometric(double p)
{
  assert(0.0<p && p<1.0);
  long result = 1+(long)(log(1.0-uniform())/log(1.0-p));
  return result;
}

long Random::pascal(long n, double p)
{ 
  assert(n>0 && 0.0<p && p<1.0);
  long y = 0;
  for(long i=0; i<n; i++) y += geometric(p);
  return y;
}

long Random::poisson(double m)
{ 
  assert(m>0);
  long y = 0;
  double t = exp(m);
  do {
    y++;
    t *= uniform();
  } while(t >= 1.0);
  y--;
  return y;
}

long *Random::permute(long n)
{
  long *array = new long[n]; assert(array);
  permute(array, n);
  return array;
}

void Random::permute(long *array, long n)
{
  long i;
  for(i=0; i<n; i++) array[i] = i;
  for(i=0; i<n-1; i++) {
    long j = equilikely(i, n-1);
    if(i != j) {
      long tmp = array[i];
      array[i] = array[j];
      array[j] = tmp;
    }
  }
}
