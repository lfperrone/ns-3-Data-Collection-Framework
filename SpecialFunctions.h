/** This class contains methods that can be used to evaluate some of the      
 'special' functions which arise in the modeling and analysis of various  
 statistical distributions.                                                

 @author Steve Park
 @author David Geyer (converted from Pascal to C)
 @author L. Felipe Perrone (converted from C to C++)
*/

#ifndef __SPECIALFUNCTIONS_H__
#define __SPECIALFUNCTIONS_H__

class SpecialFunctions {
 public:

/**
   Ln_Gamma returns the natural log of the gamma function. The algorithm used to evaluate the natural log of the gamma function is based on an approximation by C. Lanczos, SIAM J. Numerical AnalysiS, B, vol 1, 1964.  The constants have been selected to yield a relative error which is less than 2.0e-10 for all positive values of the parameter a.

@param a > 0.0                                                  
*/

  static double Ln_Gamma(double a);

/** 
    Ln_Factorial(n) returns the natural log of n! The algorithm used
    to evaluate the natural log of n! is based on a simple equation
    which relates the gamma and factorial functions.

    @param use n >= 0                                                          
*/
  static double Ln_Factorial(long n);

 /** Ln_Beta returns the natural log of the beta function. The
     algorithm used to evaluate the natural log of the beta function
     is based on a simple equation which relates the gamma and beta
     functions.

     @param use a > 0.0 and b > 0.0                                             
 */
  static double Ln_Beta(double a, double b);

  /** Ln_Choose returns the natural log of the binomial coefficient
      C(n,m). The algorithm used to evaluate the natural log of a
      binomial coefficient is based on a simple equation which relates
      the beta function to a binomial coefficient.  
      @param use 0 <= m <= n
  */

  static double Ln_Choose(long n, long m);

  /** Evaluates the incomplete gamma function. The algorithm used to
      evaluate the incomplete gamma function is based on Algorithm AS
      32, J. Applied Statistics, 1970, by G. P. Bhattacharjee. See
      also equations 6.5.29 and 6.5.31 in the Handbook of Mathematical
      Functions, Abramowitz and Stegum (editors). The absolute error
      is less than 1e-10 for all non-negative values of x.  
      @param use a > 0.0 and x >= 0.0
*/

  static double Incomplete_Gamma(double a, double x);


  /** Evaluates the incomplete beta function. The algorithm used to
      evaluate the incomplete beta function is based on equation
      26.5.8 in the Handbook of Mathematical Functions, Abramowitz and
      Stegum (editors).  The absolute error is less than 1e-10 for all
      x between 0 and 1.  
      @param use a > 0.0, b > 0.0 and 0.0 <= x <= 1.0
*/

  static double Incomplete_Beta(double a, double b, double x);
};

#endif /* __SPECIALFUNCTIONS_H__ */
