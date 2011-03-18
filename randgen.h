/**
 These are C++ classes which can be used to evaluate the probability       
 density functions (pdf's), cumulative distribution functions (cdf's), and 
 inverse distribution functions (idf's) for a variety of discrete and      
 continuous random variables.                                              
                                                                           
 The following notational conventions are used -                           
                 x : possible value of the random variable                 
                 u : real variable (probability) between 0 and 1           
  a, b, n, p, m, s : distribution specific parameters                      
                                                                    
 There are pdf's, cdf's and idf's for 6 discrete random variables:  
                                                                    
      Random Variable    Range (x)  Mean         Variance           
                                                                    
      Bernoulli(p)       0..1       p            p*(1-p)            
      Binomial(n, p)     0..n       n*p          n*p*(1-p)          
      Equilikely(a, b)   a..b       (a+b)/2      ((b-a+1)*(b-a+1)-1)/12
      Geometric(p)       0...       p/(1-p)      p/((1-p)*(1-p))       
      Pascal(n, p)       0...       n*p/(1-p)    n*p/((1-p)*(1-p))     
      Poisson(m)         0...       m            m                     
                                                                       
 and for 8 continuous random variables:                                
                                                                       
      Random Variable    Range (x)  Mean         Variance              
                                                                       
      Uniform(a, b)      a < x < b  (a+b)/2      (b-a)*(b-a)/12        
      Exponential(m)     x > 0      m            m*m                   
      Erlang(n, b)       x > 0      n*b          n*b*b                 
      Normal             all x      0            1                     
      Gauss(m, s)        all x      m            s*s                   
      Lognormal(a, b)    x > 0         see below                       
      Chisquare(n)       x > 0      n            2*n                   
      Student(n)         all x      0  (n > 1)   n/(n-2)   (n > 2)     
                                                                       
 For the Lognormal(a, b), the mean and variance are:                   
                                                                       
                        mean = Exp(a + 0.5*b*b)                        
                    variance = (Exp(b*b) - 1)*Exp(2*a + b*b)           
                                                                       
Name            : DFU.C                                                
 Purpose         : Distribution/Density Function Routines              
 Author          : Steve Park                                          
 Language        : Turbo Pascal, 5.0                                   
 Latest Revision : 09-19-90                                            
 Reference       : Lecture Notes on Simulation, by Steve Park          
 Converted to C  : David W. Geyer  09-02-91                            
*/

/* NOTE - must link with sfu.o */

class DiscreteRV {
  static double Bernoulli_pdf(double p, long x);
  static double Bernoulli_cdf(double p, long x);
  static long Bernoulli_idf(double p, double u);

  static double Equilikely_pdf(long a, long b, long x);
  static double Equilikely_cdf(long a, long b, long x);
  static double Equilikely_idf(long a, long b, double u);  

  static double Binomial_pdf(long n, double p, long x);
  static double Binomial_cdf(long n, double p, long x);
  static double Binomial_idf(long n, double p, double u);

  static double Geometric_pdf(double p, long x);
  static double Geometric_cdf(double p, long x);
  static long Geometric_idf(double p, double u);

  static double Pascal_pdf(long n, double p, long x);
  static double Pascal_cdf(long n, double p, long x);
  static long Pascal_idf(long n, double p, double u);

  static double Poisson_pdf(double m, long x);
  static double Poisson_cdf(double m, long x);
  static long Poisson_idf(double m, double u);
};

class ContinuousRV {
  static double Uniform_pdf(double a, double b, double x);
  static double Uniform_cdf(double a, double b, double x);
  static double Uniform_idf(double a, double b, double u);

  static double Exponential_pdf(double m, double x);
  static double Exponential_cdf(double m, double x);
  static double Exponential_idf(double m, double u);

  static double Erlang_pdf(long n, double b, double x);
  static double Erlang_cdf(long n, double b, double x);
  static double Erlang_idf(long n, double b, double u);

  static double Normal_pdf (double x);
  static double Normal_cdf (double x);
  static double Normal_idf (double u);

  static double Gauss_pdf(double m, double s, double x);
  static double Gauss_cdf(double m, double s, double x);
  static double Gauss_idf(double m, double s, double u);

  static double Lognormal_pdf(double a, double b, double x);
  static double Lognormal_cdf(double a, double b, double x);
  static double Lognormal_idf(double a, double b, double u);

  static double Chisquare_pdf(long n, double x);
  static double Chisquare_cdf(long n, double x);
  static double Chisquare_idf(long n, double u);

  static double Student_pdf(long n, double x);
  static double Student_cdf(long n, double x);
  static double Student_idf(long n, double u);
};


/* ========================================================================= */
/*                        double Equilikely_pdf()                            */
/*                        double Equilikely_cdf()                            */
/*                         long  Equilikely_idf()                            */
/*                                                                           */
/* NOTE: use a <= x <= b and 0 < u < 1                                       */
/* ========================================================================= */

/* ========================================================================= */
/*                          double Binomial_pdf()                            */
/*                          double Binomial_cdf()                            */
/*                           long  Binomial_idf()                            */
/*                                                                           */
/* NOTE: use 0 <= x <= n, 0 < p < 1 and 0 < u < 1                            */
/* ========================================================================= */

/* ========================================================================= */
/*                         double Geometric_pdf()                            */
/*                         double Geometric_cdf()                            */
/*                          long  Geometric_idf()                            */
/*                                                                           */
/* NOTE: use 0 < p < 1, x >= 0 and 0 < u < 1                                 */
/* ========================================================================= */

/* ========================================================================= */
/*                            double Pascal_pdf()                            */
/*                            double Pascal_cdf()                            */
/*                             long  Pascal_idf()                            */
/*                                                                           */
/* NOTE: use n >= 1, 0 < p < 1, x >= 0 and 0 < u < 1                         */
/* ========================================================================= */

/* ========================================================================= */
/*                          double Poisson_pdf()                             */
/*                          double Poisson_cdf()                             */
/*                           long  Poisson_idf()                             */
/*                                                                           */
/* NOTE: use m > 0, x >= 0 and 0 < u < 1                                     */
/* ========================================================================= */

/* ========================================================================= */
/*                          double Uniform_pdf()                             */
/*                          double Uniform_cdf()                             */
/*                          double Uniform_idf()                             */
/*                                                                           */
/* NOTE: use a < x < b and 0 < u < 1                                         */
/* ========================================================================= */


/* ========================================================================= */
/*                        double Exponential_pdf()                           */
/*                        double Exponential_cdf()                           */
/*                        double Exponential_idf()                           */
/*                                                                           */
/* NOTE: use m > 0, x > 0 and 0 < u < 1                                      */
/* ========================================================================= */


/* ========================================================================= */
/*                          double Erlang_pdf()                              */
/*                          double Erlang_cdf()                              */
/*                          double Erlang_idf()                              */
/*                                                                           */
/* NOTE: use n >= 1, b > 0, x > 0 and 0 < u < 1                              */
/* ========================================================================= */


/* ========================================================================= */
/*                          double Normal_pdf()                              */
/*                          double Normal_cdf()                              */
/*                          double Normal_idf()                              */
/*                                                                           */
/* NOTE: x can be any value, but 0 < u < 1                                   */
/* ========================================================================= */


/* ========================================================================= */
/*                           double Gauss_pdf()                              */
/*                           double Gauss_cdf()                              */
/*                           double Gauss_idf()                              */
/*                                                                           */
/* NOTE: x and m can be any value, but s > 0 and 0 < u < 1                   */
/* ========================================================================= */


/* ========================================================================= */
/*                          double Lognormal_pdf()                           */
/*                          double Lognormal_cdf()                           */
/*                          double Lognormal_idf()                           */
/*                                                                           */
/* NOTE: a can have any value, but b > 0, x > 0 and 0 < u < 1                */
/* ========================================================================= */


/* ========================================================================= */
/*                          double Chisquare_pdf()                           */
/*                          double Chisquare_cdf()                           */
/*                          double Chisquare_idf()                           */
/*                                                                           */
/* NOTE: use n >= 1, x > 0 and 0 < u < 1                                     */
/* ========================================================================= */

/* ========================================================================= */
/*                           double Student_pdf()                            */
/*                           double Student_cdf()                            */
/*                           double Student_idf()                            */
/*                                                                           */
/* NOTE: use n >= 1, x > 0 and 0 < u < 1                                     */
/* ========================================================================= */

