/*
 * rng.h : this file was extracted from DaSSF, where it was the
 * kernel random number generator. (kernelrng.h)
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

/* The first random generator is a so-called 'Lehmer random number generator' 
 * which returns a pseudo-random number uniformly distributed 0.0 and 1.0.
 * The period is (m - 1) where m = 2,147,483,647 and the smallest and largest 
 * possible values are (1 / m) and 1 - (1 / m) respectively.  For more details 
 * see: "Random Number Generators: Good Ones Are Hard To Find", by Steve Park 
 * and Keith Miller, Communications of the ACM, October 1988.
 *
 * This second random number generator is called "Mersenne Twister", which is
 * used to create a stream from which pseudo random numbers may be pulled and 
 * used to generate smaller streams for parallel processors.  It is modified 
 * by Allison Davis (allison.r.davis@dartmouth.edu) July 10, 1998 from code by 
 * Shawn Cokus March 8, 1998 which is the ``Mersenne Twister'' random number 
 * generator MT19937, which generates pseudorandom integers uniformly distributed
 * in 0..[2^32 - 1] starting from any odd seed in 0..[2^32 - 1].  This version is 
 * a recode by Shawn Cokus [Cokus@math.washington.edu] on March 8, 1998 of a 
 * version by Takuji Nishimura [who had suggestions from Topher Cooper and Marc 
 * Rieffel in July-August 1997].
 *
 * Effectiveness of the recoding (on Goedel2.math.washington.edu, a DEC Alpha
 * running OSF/1) using GCC -O3 as a compiler: before recoding: 51.6 sec. to
 * generate 300 million random numbers; after recoding: 24.0 sec. for the same
 * (i.e., 46.5% of original time), so speed is now about 12.5 million random
 * number generations per second on this machine.
 *
 * According to the URL <http://www.math.keio.ac.jp/~matumoto/emt.html>
 * (and paraphrasing a bit in places), the Mersenne Twister is ``designed
 * with consideration of the flaws of various existing generators,'' has
 * a period of 2^19937 - 1, gives a sequence that is 623-dimensionally
 * equidistributed, and ``has passed many stringent tests, including the
 * die-hard test of G. Marsaglia and the load test of P. Hellekalek and
 * S. Wegenkittl.''  It is efficient in memory usage (typically using 2506
 * to 5012 bytes of static data, depending on data type sizes, and the code
 * is quite short as well).  It generates random numbers in batches of 624
 * at a time, so the caching and pipelining of modern systems is exploited.
 * It is also divide- and mod-free.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Library General Public License as published by
 * the Free Software Foundation (either version 2 of the License or, at your
 * option, any later version).  This library is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY, without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 * the GNU Library General Public License for more details.  You should have
 * received a copy of the GNU Library General Public License along with this
 * library; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307, USA.
 *
 * The code as Shawn received it included the following notice:
 *
 *   Copyright (C) 1997 Makoto Matsumoto and Takuji Nishimura.  When
 *   you use this, send an e-mail to <matumoto@math.keio.ac.jp> with
 *   an appropriate reference to your work.
 *
 * It would be nice to CC: <Cokus@math.washington.edu> when you write.
 */

#ifndef __RNG_H__
#define __RNG_H__

class Base_Generator;
class Rng;
class RngLehmer;
class RngMT;

/** rng_uint32 must be an unsigned integer type capable of holding at
least 32 bits; exactly 32 should be fastest, but 64 is better on an
Alpha with GCC at -O3 optimization so try your options and see whats
best for you.
*/

typedef unsigned long long rng_uint32; /* need 64-bit type */

#define RND_N          (624)                 // length of state vector
#define RND_M          (397)                 // a period parameter
#define RND_K          (0x9908B0DFUL)        // a magic constant
#define hiBit(u)       ((u) & 0x80000000UL)  // mask all but highest   bit of u
#define loBit(u)       ((u) & 0x00000001UL)  // mask all but lowest    bit of u
#define loBits(u)      ((u) & 0x7fffffffUL)  // mask     the highest   bit of u
#define mixBits(u, v)  (hiBit(u)|loBits(v))  // move hi bit of u to hi bit of v

class Base_Generator
{
protected:
    //state variables
    rng_uint32 *next;           // next random value is computed from here
    rng_uint32 state[RND_N+1];  // state vector +1 extra to not violate ANSI C
    int left;                   // can *next++ this many times before reloading
    // action functions
    void seedMT(rng_uint32 seed);
    rng_uint32 reloadMT(void);

public:
    /// Constructor. you may seed with any rng_uint32, but the best are odd values.
    Base_Generator(rng_uint32 seed);           

    /// Default constructor necessary for inheritance. Does nothing.
    Base_Generator() {/*does nothing*/};       // in 0...(2^32 - 1) 

    /// Returns a random number.
    rng_uint32 randomMT(void);
};

/** Base random number generator class. */
class Rng 
{
public:
  /// Constructor
  Rng() {}

  /// Destructor
  virtual ~Rng() {}
  
  /// Generates a random number in [0,1]
  virtual double get_random01() { return 0; }

  /// Set seed of the generator
  virtual void set_seed(long seed) {}

  /// Retrieve current seed value of the generator
  virtual long get_seed() { return 12345;}
};


/** Mersenne Twister random number generator class. */
class RngMT : public Rng, public Base_Generator
{
 public:
  /// Constructor
  RngMT(long seed = 0);
  
  /// Destructor
  virtual ~RngMT() {}

  /// Generates a random number in [0,1]
  virtual double get_random01();
  
  /// Set seed of the generator
  virtual void set_seed(long seed);
  
  /// Retrieve current seed value of the generator
  virtual long get_seed();
};

/** Lehmer (linear congruential) random number generator class. */
class RngLehmer : public Rng
{
 protected:
  long seed;

public:
  /// Constructor
  RngLehmer(long seed = 0);
  
  /// Destructor
  virtual ~RngLehmer() {}

  /// Generates a random number in [0,1]
  virtual double get_random01();

  /// Set seed of the generator
  virtual void set_seed(long seed);

  /// Retrieve current seed value of the generator
  virtual long get_seed();  
};

#endif /*__RNG_H__*/



