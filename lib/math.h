#ifndef MATH_H
#define MATH_H

#define NAN (__builtin_nanf (""))

#define isnan(x) __builtin_isnan (x)


double fabs(double x);
double fmin(double x, double y);
double fmax(double x, double y);

double ceil(double x);

uint32_t __popcountdi2(double a);
uint32_t __popcountsi2(int32_t a);

int signbit(double x);
double floor(double x);
double trunc(double x);
double rint(double x);
double sqrt(double x);

#endif // MATH_H
