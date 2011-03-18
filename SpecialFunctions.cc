#include <cmath>
#include <cstdio>

#include "SpecialFunctions.h"

#define ABS(a) ( (a > 0) ? a : -(a) )

double SpecialFunctions::Ln_Gamma(double a)
{ double c = 2.506628274631;                     /* Sqrt(2 * pi) */
  double s[6], sum, temp;
  int    i;

  s[0] =  76.180091729406 / a;
  s[1] = -86.505320327112 / (a + 1);
  s[2] =  24.014098222230 / (a + 2);
  s[3] =  -1.231739516140 / (a + 3);
  s[4] =   0.001208580030 / (a + 4);
  s[5] =  -0.000005363820 / (a + 5);
  sum  =   1.000000000178;
  for (i=0;i < 6;i++)
    sum += s[i];
  temp = (a - 0.5) * log(a + 4.5) - (a + 4.5) + log(c * sum);
  return(temp);
}  /* Ln_Gamma */

double SpecialFunctions::Ln_Factorial(long n)
{ 
  return(Ln_Gamma((double)n + (double)1.0));
}  /* Ln_Factorial */

double SpecialFunctions::Ln_Beta(double a, double b)
{ double temp;

  temp    = Ln_Gamma(a) + Ln_Gamma(b) - Ln_Gamma(a + b);

  printf("Ln_Beta(%lf, %lf) = %lf\n", a, b, temp);

  return(temp);
}  /* Ln_Beta */

double SpecialFunctions::Ln_Choose(long n, long m)
{
  if (m > 0)
    return(- Ln_Beta((double)m, (double)(n - m + 1)) - log((double)m));
  else
    return((double) 0.0);
}  /* Ln_Choose */

double SpecialFunctions::Incomplete_Gamma(double a, double x)
{ double tiny = 1.0e-10;                      /* convergence parameter */
  double t, sum, term, factor, f, g, c[2], p[3], q[3];
  long   n;

  if (x > 0.0)
    factor = exp(-x + a * log(x) - Ln_Gamma(a));
  else
    factor = 0.0;
  if (x < a + 1.0) {                 /* evaluate as an infinite series - */
      t    = a;                      /* A & S equation 6.5.29            */
      term = 1.0 / a;
      sum  = term;
      do {                           /* sum until 'term' is small */
        t++;
        term *= x / t;
        sum  += term;
      } while (term >= tiny * sum);
      return(factor * sum);
  }

  else  {                            /* evaluate as a continued fraction - */
    p[0]  = 0.0;                     /* A & S eqn 6.5.31 with the extended */
    q[0]  = 1.0;                     /* pattern 2-a, 2, 3-a, 3, 4-a, 4,... */
    p[1]  = 1.0;                     /* - see also A & S sec 3.10, eqn (3) */
    q[1]  = x;
    f     = p[1] / q[1];
    n     = 0;
    do {                             /* recursively generate the continued */
      g  = f;                        /* fraction 'f' until two consecutive */
      n++;                           /* values are small                   */
      if ((n%2) > 0) {
        c[0] = ((double)(n + 1) / 2) - a;
        c[1] = 1.0;
      }
      else  {
        c[0] = (double)(n / 2);
        c[1] = x;
      }
      p[2] = c[1] * p[1] + c[0] * p[0];
      q[2] = c[1] * q[1] + c[0] * q[0];
      if (q[2] != 0.0)  {             /* rescale to avoid overflow */
          p[0] = p[1] / q[2];
          q[0] = q[1] / q[2];
          p[1] = p[2] / q[2];
          q[1] = 1.0;
          f    = p[1];
      }
    } while ((fabs(f - g) >= tiny) || (q[1] != 1.0));
    return((double)1.0 - factor * f);
  }
}  /* Incomplete_Gamma */

double SpecialFunctions::Incomplete_Beta(double a, double b, double x)
{ double tiny = 1.0e-10;                      /* convergence parameter */
  double t, factor, f, g, c, p[3], q[3];
  bool swap;
  long   n;

  if (x > (a + 1) / (a + b + 1)) {   /* to accelerate convergence   */
    swap = true;                     /* complement x and swap a & b */
    x    = 1 - x;
    t    = a;
    a    = b;
    b    = t;
  }
  else                                /* do nothing */
    swap = false;
  if (x > 0)
    factor = exp(a * log(x) + b * log(1 - x) - Ln_Beta(a,b)) / a;
  else
    factor = 0;
  p[0] = 0;
  q[0] = 1;
  p[1] = 1;
  q[1] = 1;
  f    = p[1] / q[1];
  n    = 0;
  do {                               /* recursively generate the continued */
    g = f;                           /* fraction 'f' until two consecutive */
    n++;                             /* values are small                   */
    if ((n%2) > 0)  {
      t = (n - 1) / 2;
      c = -(a + t) * (a + b + t) * x / ((a + n - 1) * (a + n));
    }
    else  {
      t = n / 2;
      c = t * (b - t) * x / ((a + n - 1) * (a + n));
    }
    p[2] = p[1] + c * p[0];
    q[2] = q[1] + c * q[0];
    if (q[2] != 0)  {                /* rescale to avoid overflow */
      p[0] = p[1] / q[2];
      q[0] = q[1] / q[2];
      p[1] = p[2] / q[2];
      q[1] = 1.0;
      f    = p[1];
    }
  } while ((ABS(f - g) >= tiny) || (q[1] != 1));
  if (swap)
    return(1.0 - factor * f);
  else
    return(factor * f);
}  /* Incomplete_Beta */
