/*
 * rng.cc : this file was extracted from DaSSF, where it was the
 * kernel random number generator. (kernelrng.cc)
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

#include <assert.h>
#include <cmath>

#include "rng.h"

using namespace std;

Base_Generator::Base_Generator(rng_uint32 seed)
{
  // base generator generates random seeds for future streams
  left = -1;
  seedMT(seed);
}

void Base_Generator::seedMT(rng_uint32 seed)
{
  //
  // We initialize state[0..(RND_N-1)] via the generator
  //
  //   x_new = (69069 * x_old) mod 2^32
  //
  // from Line 15 of Table 1, p. 106, Sec. 3.3.4 of Knuth's
  // _The Art of Computer Programming_, Volume 2, 3rd ed.
  //
  // Notes (SJC): I do not know what the initial state requirements
  // of the Mersenne Twister are, but it seems this seeding generator
  // could be better.  It achieves the maximum period for its modulus
  // (2^30) iff x_initial is odd (p. 20-21, Sec. 3.2.1.2, Knuth); if
  // x_initial can be even, you have sequences like 0, 0, 0, ...;
  // 2^31, 2^31, 2^31, ...; 2^30, 2^30, 2^30, ...; 2^29, 2^29 + 2^31,
  // 2^29, 2^29 + 2^31, ..., etc. so I force seed to be odd below.
  //
  // Even if x_initial is odd, if x_initial is 1 mod 4 then
  //
  //   the          lowest bit of x is always 1,
  //   the  next-to-lowest bit of x is always 0,
  //   the 2nd-from-lowest bit of x alternates      ... 0 1 0 1 0 1 0 1 ... ,
  //   the 3rd-from-lowest bit of x 4-cycles        ... 0 1 1 0 0 1 1 0 ... ,
  //   the 4th-from-lowest bit of x has the 8-cycle ... 0 0 0 1 1 1 1 0 ... ,
  //    ...
  //
  // and if x_initial is 3 mod 4 then
  //
  //   the          lowest bit of x is always 1,
  //   the  next-to-lowest bit of x is always 1,
  //   the 2nd-from-lowest bit of x alternates      ... 0 1 0 1 0 1 0 1 ... ,
  //   the 3rd-from-lowest bit of x 4-cycles        ... 0 0 1 1 0 0 1 1 ... ,
  //   the 4th-from-lowest bit of x has the 8-cycle ... 0 0 1 1 1 1 0 0 ... ,
  //    ...
  //
  // The generator's potency (min. s>=0 with (69069-1)^s = 0 mod 2^32) is
  // 16, which seems to be alright by p. 25, Sec. 3.2.1.3 of Knuth.  It
  // also does well in the dimension 2..5 spectral tests, but it could be
  // better in dimension 6 (Line 15, Table 1, p. 106, Sec. 3.3.4, Knuth).
  //
  // Note that the random number user does not see the values generated
  // here directly since reloadMT() will always munge them first, so maybe
  // none of all of this matters.  In fact, the seed values made here could
  // even be extra-special desirable if the Mersenne Twister theory says
  // so-- that's why the only change I made is to restrict to odd seeds.
  //

  register rng_uint32 x = (seed | 1UL) & 0xffffffffUL, *s = state;
  register int    j;

  for(left=0, *s++=x, j=RND_N; --j;
      *s++ = (x*=69069UL) & 0xffffffffUL);
}


rng_uint32 Base_Generator::reloadMT(void)
{
  register rng_uint32 *p0=state, *p2=state+2, *pM=state+RND_M, s0, s1;
  register int    j;

  if(left < -1)
    seedMT(4357UL);

  left=RND_N-1, next=state+1;

  for(s0=state[0], s1=state[1], j=RND_N-RND_M+1; --j; s0=s1, s1=*p2++)
    *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? RND_K : 0UL);

  for(pM=state, j=RND_M; --j; s0=s1, s1=*p2++)
    *p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? RND_K : 0UL);

  s1=state[0], *p0 = *pM ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? RND_K : 0UL);
  s1 ^= (s1 >> 11);
  s1 ^= (s1 <<  7) & 0x9d2c5680UL;
  s1 ^= (s1 << 15) & 0xefc60000UL;
  return(s1 ^ (s1 >> 18));
}


rng_uint32 Base_Generator::randomMT(void)
{
  rng_uint32 y;

  if(--left < 0)
    return(reloadMT());

  y  = *next++;
  y ^= (y >> 11);
  y ^= (y <<  7) & 0x9d2c5680UL;
  y ^= (y << 15) & 0xefc60000UL;
  return(y ^ (y >> 18));
}


RngMT::RngMT(long _seed) : Rng(), Base_Generator()
{
  set_seed(_seed);
}

double RngMT::get_random01()
{
  unsigned long bign = 0xffffffffUL;
  return (((double)randomMT())/bign);
}

void RngMT::set_seed(long _seed)
{
  left = -1;
  if(_seed == 0) seedMT(1234567890);
  else seedMT((rng_uint32)_seed);
}

long RngMT::get_seed() 
{
  return 777;
}

#define RND_MODULUS    2147483647UL
#define RND_MULTIPLIER 48271UL
#define RND_Q        (RND_MODULUS/RND_MULTIPLIER)
#define RND_R        (RND_MODULUS%RND_MULTIPLIER)

RngLehmer::RngLehmer(long _seed) : Rng()
{
  set_seed(_seed);
}

double RngLehmer::get_random01()
{
  long t = RND_MULTIPLIER*(seed%RND_Q)-RND_R*(seed/RND_Q);
  if(t > 0) seed = t;
  else seed = t + RND_MODULUS;
  return (double)seed/RND_MODULUS;
}

void RngLehmer::set_seed(long _seed)
{
  if(_seed == 0) 
    seed = (long)(1234567890 & 0x0fffffffUL);
  else {
    seed = _seed;
    if(seed <= 0) seed += RND_MODULUS;
  }
}

long RngLehmer::get_seed() {
  return seed;
}

#undef RND_R
#undef RND_Q
#undef RND_MULTIPLIER
#undef RND_MODULUS

