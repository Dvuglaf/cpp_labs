#include <stdio.h>
#include <stdlib.h>
#include "c_func.h"
#include <libutils/io.h>
#include <float.h>
using namespace c;
func c::Sum(const func f1, const func f2)
{
	func result;
	result.a = f1.a + f2.a;
	result.b = f1.b + f2.b;
	result.c = f1.c + f2.c;
	return result;
}
func c::Dif(const func f1, const func f2)
{
	func result;
	result.a = f1.a - f2.a;
	result.b = f1.b - f2.b;
	result.c = f1.c - f2.c;
	return result;
}
void c::Deriv(func *f1)
{
	(*f1).c = (*f1).b;
	(*f1).b = (*f1).a * 2;
	(*f1).a = 0;
}
double c::Point(const func f1, double x)
{
	return (f1.a*x*x + f1.b*x + f1.c);
}
void c::Enter(func *f1)
{
	(*f1).a = utils::read_double("Enter a: ", -DBL_MAX, DBL_MAX, EPS);
	(*f1).b = utils::read_double("Enter b: ", -DBL_MAX, DBL_MAX, EPS);
	(*f1).c = utils::read_double("Enter c: ", -DBL_MAX, DBL_MAX, EPS);
}
void c::Print(const func f1, const char *name)
{
	printf("%s(x) = ",name);
	if (f1.a == 0 && f1.b == 0 && f1.c == 0)
		printf("0\n");
	if (f1.a != 0)
		printf("%.3lfx^2",f1.a);
	if (f1.b < 0)
		printf("%.3lfx", f1.b);
	if (f1.b > 0)
	{
		if (f1.a != 0)
			printf("+");
		printf("%.3lfx", f1.b);
	}
	if (f1.c < 0)
		printf("%.3lf", f1.c);
	if (f1.c > 0)
	{
		if (f1.b != 0)
			printf("+");
		printf("%.3lf", f1.c);
	}
	printf("\n");
}