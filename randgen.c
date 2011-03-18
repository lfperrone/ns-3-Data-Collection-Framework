#include <math.h>                          /* for log(), exp(), abs() */
#define ABS(a) ( (a > 0) ? a : -(a) )

double DiscreteRV::Bernoulli_pdf(double p, x)
{
  if (x == 0)
    return((double)1.0 - p);
  else
    return(p);
}  /* Bernoulli_pdf */

double DiscreteRV::Bernoulli_cdf(double p, long x)
{
  if (x == 0)
    return((double)1.0 - p);
  else
    return((double)1.0);
}  /* Bernoulli_cdf */

long DiscreteRV::Bernoulli_idf(double p, long u)
{
  if (u < ((double)1.0 - p))
    return((double)0.0);
  else
    return((double)1.0);
}  /* Bernoulli_idf */

double DiscreteRV::Equilikely_pdf(long a, long b, long x)
{
  return( (double)1.0 / ((double)b - (double)a + (double)1.0) );
}  /* Equilikely_pdf */

double DiscreteRV::Equilikely_cdf(long a, long b, long x)
{
  return( ((double)x - (double)a + (double)1.0) /
          ((double)b - (double)a + (double)1.0)  );
}  /* Equilikely_cdf */

long DiscreteRV::Equilikely_idf(long a, long b, double u)
{
  return(a + (long)(u * (b - a + 1)) );
}  /* Equilikely_idf */

double DiscreteRV::Binomial_pdf(long n, double p, long x)
{ double s, t, Ln_Choose();

  s = Ln_Choose(n, x);                   /* break this calculation        */
  t = x * log(p) + (n - x) * log(1 - p); /* into two parts                */
  return(exp(s + t));                    /* to avoid 80x87 stack overflow */
}  /* Binomial_pdf */

double DiscreteRV::Binomial_cdf(long n, double p, long x)
{ double Incomplete_Beta();

  if (x < n)
    return((double)1.0 - Incomplete_Beta((double)(x+1), (double)(n-x), p));
  else
    return((double)1.0);
}  /* Binomial_cdf */

long DiscreteRV::Binomial_idf(long n, double p, double u)
{ long  x;
  double Binomial_cdf();

  x = (long)(n * p);                         /* start searching at the mean */
  if (Binomial_cdf(n, p, x) <= u)
    while (Binomial_cdf(n, p, x) <= u)  {
      x++;
    }
  else if (Binomial_cdf(n, p, 0) <= u)
    while (Binomial_cdf(n, p, x - 1) > u)  {
      x--;
    }
  else
    x = 0;
  return(x);
}  /* Binomial_idf */

double DiscreteRV::Geometric_pdf(double p, long x)
{
  return( (1.0 - p) * exp(x * log(p)) );
}  /* Geometric_pdf */

double DiscreteRV::Geometric_cdf(double p, long x)
{
  return( 1.0 - exp((x + 1) * log(p)) );
}  /* Geometric_cdf */

long DiscreteRV::Geometric_idf(double p, double u)
{
  return( (long)(log(1.0 - u) / log(p)) );
}  /* Geometric_idf */

double DiscreteRV::Pascal_pdf(long n, double p, long x)
{ double  s, t, Ln_Choose();

  s = Ln_Choose(n + x - 1, x);            /* break this calculation        */
  t = x * log(p) + n * log(1.0 - p);      /* into two parts                */
  return(exp(s + t));                     /* to avoid 80x87 stack overflow */
}  /* Pascal_pdf */

double DiscreteRV::Pascal_cdf(long n, double p, long x)
{ double  Incomplete_Beta();

  return(1.0 - Incomplete_Beta(x + 1, n, p));
}  /* Pascal_cdf */

long DiscreteRV::Pascal_idf(long n, double p, double u)
{ long  x;

  x = (long)(n * p / (1.0 - p));            /* start searching at the mean */
  if (Pascal_cdf(n, p, x) <= u)
    while (Pascal_cdf(n, p, x) <= u)  {
      x++;
    }
  else if (Pascal_cdf(n, p, 0) <= u)
    while (Pascal_cdf(n, p, x - 1) > u)  {
      x--;
    }
  else
    x = 0;
  return(x);
}  /* Pascal_idf */

double DiscreteRV::Poisson_pdf(double m, long x)
{ double t, Ln_Factorial();

  t = - m + x * log(m) - Ln_Factorial(x);
  return(exp(t));
}  /* Poisson_pdf */

double DiscreteRV::Poisson_cdf(double m, long x)
{ double Incomplete_Gamma();

  return((double)1.0 - Incomplete_Gamma((double)x + 1.0, m));
}  /* Poisson_cdf */

long DiscreteRV::Poisson_idf(double m, long u)
{ long x;
  double Poisson_cdf();

  x = (long)m;                            /* start searching at the mean */
  if (Poisson_cdf(m, x) <= u)
    while (Poisson_cdf(m, x) <= u)  {
      x++;
    }
  else if (Poisson_cdf(m, 0) <= u)
    while (Poisson_cdf(m, x - 1) > u)  {
      x--;
    }
  else
    x = 0;
  return(x);
}  /* Poisson_idf */

double ContinuousRV::Uniform_pdf(double a, double b, double x)
{
  return(1.0 / (b - a));
}  /* Uniform_pdf */

double ContinuousRV::Uniform_cdf(double a, double b, double x)
{
  return((x - a) / (b - a));
}  /* Uniform_cdf */

double ContinuousRV::Uniform_idf(double a, double b, double u)
{
  return(a + (b - a) * u);
}  /* Uniform_idf */

double ContinuousRV::Exponential_pdf(double m, double x)
{
  return((1.0 / m) * exp(- x / m));
}  /* Exponential_pdf */

double ContinuousRV::Exponential_cdf(double m, double x)
{
  return(1.0 - exp(- x / m));
}  /* Exponential_cdf */

double ContinuousRV::Exponential_idf(double m, double u)
{
  return(- m * log(1 - u));
}  /* Exponential_idf */

double ContinuousRV::Erlang_pdf(long n, double b, double x)
{ double t, Ln_Gamma();

  t = (double)(n - 1) * log(x / b) - (x / b) - log(b) - Ln_Gamma((double)n);
  return(exp(t));
}  /* Erlang_pdf */

double ContinuousRV::Erlang_cdf(long n, double b, double x)
{ double Incomplete_Gamma();

  return(Incomplete_Gamma((double)n, x / b));
}  /* Erlang_cdf */

double ContinuousRV::Erlang_idf(long n, double b, double u)
{ double tiny = 1.0e-10, t, x, Erlang_cdf(), Erlang_pdf();

  x = (double)n * b;                 /* initialize to the mean, then - */
  do {                               /* use Newton-Raphson iteration   */
    t = x;
    x = t + (u - Erlang_cdf(n, b, t)) / Erlang_pdf(n, b, t);
    if (x <= 0.0)
      x = 0.5 * t;
  } while (fabs(x - t) >= tiny);
  return(x);
}  /* Erlang_idf */

double ContinuousRV::Normal_pdf(double x)
{ double c = 0.3989422804;                          /* 1 / Sqrt(2 * pi) */

  return(c * exp(-0.5 * x * x));
}  /* Normal_pdf */

double ContinuousRV::Normal_cdf(double x)
{ double t, Incomplete_Gamma();

  t = Incomplete_Gamma(0.5, 0.5 * x * x);
  if (x < 0.0)
    return(0.5 * (1.0 - t));
  else
    return(0.5 * (1.0 + t));
}  /* Normal_cdf */

double ContinuousRV::Normal_idf(double u)
{ double tiny = 1.0e-10, t, x, Normal_cdf(), Normal_pdf();

  x = 0.0;                           /* initialize to the mean, then - */
  do {                               /* use Newton-Raphson iteration   */
    t = x;
    x = t + (u - Normal_cdf(t)) / Normal_pdf(t);
  } while (abs(x - t) >= tiny);
  return(x);
}  /* Normal_idf */

double ContinuousRV::Gauss_pdf(double m, double s, double x)
{ double t, Normal_pdf();

  t = (x - m) / s;
  return(Normal_pdf(t) / s);
}  /* Gauss_pdf */

double ContinuousRV::Gauss_cdf(double m, double s, double x)
{ double t, Normal_cdf();

  t = (x - m) / s;
  return(Normal_cdf(t));
}  /* Gauss_cdf */

double ContinuousRV::Gauss_idf(double m, double s, double u)
{ double Normal_idf();

  return(m + s * Normal_idf(u));
}  /* Gauss_idf */

double ContinuousRV::Lognormal_pdf(double a, double b, double x)
{ double t, Normal_pdf();

  t = (log(x) - a) / b;
  return(Normal_pdf(t) / (b * x));
}  /* Lognormal_pdf */

double ContinuousRV::Lognormal_cdf(double a, double b, double x)
{ double t, Normal_cdf();

  t = (log(x) - a) / b;
  return(Normal_cdf(t));
}  /* Lognormal_cdf */

double ContinuousRV::Lognormal_idf(double a, double b, double u)
{ double t, Normal_idf();

  t = a + b * Normal_idf(u);
  return(exp(t));
}  /* Lognormal_idf */

double ContinuousRV::Chisquare_pdf(long n, double x)
{ double t, Ln_Gamma();

  t = (n / 2 - 1) * log(x / 2) - (x / 2) - log(2) - Ln_Gamma(n / 2);
  return(exp(t));
}  /* Chisquare_pdf */

double ContinuousRV::Chisquare_cdf(long n, double x)
{ double Incomplete_Gamma();

  return(Incomplete_Gamma(n / 2, x / 2));
}  /* Chisquare_cdf */

double ContinuousRV::Chisquare_idf(long n, double u)
{ double tiny = 1.0e-10, t, x, Chisquare_cdf(), Chisquare_pdf();

  x = n;                               /* initialize to the mean, then - */
  do {                                 /* use Newton-Raphson iteration   */
    t = x;
    x = t + (u - Chisquare_cdf(n, t)) / Chisquare_pdf(n, t);
    if (x <= 0)
      x = 0.5 * t;
  } while (abs(x - t) >= tiny);
  return(x);
}  /* Chisquare_idf */

double ContinuousRV::Student_pdf(long n, double x)
{ double t, Ln_Beta();

  t = -0.5 * (n + 1) * log(1 + ((x * x) / (double)n))
                                     - Ln_Beta(0.5, (double)n / 2.0);
  return(exp(t) / sqrt((double)n));
}  /* Student_pdf */

double ContinuousRV::Student_cdf(long n, double x)
{ double s, t, Incomplete_Beta();

  t = (x * x) / (n + x * x);
  s = Incomplete_Beta(0.5, (double)n / 2.0, t);
  if (x >= 0)
    return(0.5 * (1.0 + s));
  else
    return(0.5 * (1.0 - s));
}  /* Student_cdf */

double ContinuousRV::Student_idf(long n, double u)
{ double tiny = 1.0e-10, t, x, Student_cdf(), Student_pdf();

  x = 0;                              /* initialize to the mean, then - */
  do {                                /* use Newton-Raphson iteration   */
    t = x;
    x = t + (u - Student_cdf(n, t)) / Student_pdf(n, t);
  } while (ABS(x - t) >= tiny);
  return(x);
}  /* Student_idf */
