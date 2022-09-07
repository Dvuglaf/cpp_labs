#include <cstdio>
#include <cstdlib>
#include "cpp_func.h"
#include <libutils/io.h>
#include <cfloat>
using namespace cpp;
	Func Func::Sum(const Func &f2) const
	{
		return Func(_a + f2.Get_a(), _b + f2.Get_b(), _c + f2.Get_c());
	}
	
	void Func::Enter()
	{
		_a = utils::read_double("Enter a: ", -DBL_MAX, DBL_MAX, EPS);
		_b = utils::read_double("Enter b: ", -DBL_MAX, DBL_MAX, EPS);
		_c = utils::read_double("Enter c: ", -DBL_MAX, DBL_MAX, EPS);
	}
	void Func::Print(const char* name) const
	{
		printf("%s(x) = ", name);
		if (_a == 0 && _b == 0 && _c == 0)
			printf("0\n");
		if (_a != 0)
			printf("%.3lfx^2", _a);
		if (_b < 0)
			printf("%.3lfx", _b);
		if (_b > 0)
		{
			if (_a != 0)
				printf("+");
			printf("%.3lfx", _b);
		}
		if (_c < 0)
			printf("%.3lf", _c);
		if (_c > 0)
		{
			if (_b != 0)
				printf("+");
			printf("%.3lf", _c);
		}
		printf("\n");
	}

	Func Func::StaticDif(const Func &f1, const Func &f2) 
	{
		return f1.Dif(f2);
	}

	Func Func::Dif(const Func& f2) const
	{
		return Func(_a - f2.Get_a(), _b - f2.Get_b(),_c - f2.Get_c());
	}
	void Func::Deriv()
	{
		_c = _b;
		_b = 2 * _a;
		_a = 0;
	}
	double Func::Point(double x) const
	{
		return (_a * x * x + _b * x + _c);
	}
	double  Func::Get_a() const
	{
		return _a;
	}
	double  Func::Get_b() const
	{
		return _b;
	}
	double  Func::Get_c() const
	{
		return _c;
	}
	void Func::Set_a(double a) { _a = a; }
	void Func::Set_b(double b) { _b = b; }
	void Func::Set_c(double c) { _c = c; }

