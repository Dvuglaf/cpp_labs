/*#include <stdio.h>
#include <stdlib.h>
#include "c_func.h"
#include <libutils/io.h>
#include "cpp_func.h"
#include <float.h>
int main()
{
	bool c = true;
	while (1)
	{
		system("cls");
		if(c)
			printf("***********\nC - ON\nC++ - OFF\n\n***********\n");
		else
			printf("***********\nC - OFF\nC++ - ON\n\n***********\n");
		printf("1.Summorise\n2.Difference\n3.Derivative\n4.Point\n5.Switch to C/C++\n0.Exit\n");
		int value = utils::read_int("Enter a number: ", 0, 5);
		if (value == 5)
			c = !c;
		else if (value == 0)
			return 0;
		if (c)
		{
			c::func f1, f2, res;
			if (value == 1)
			{
				system("cls");
				printf("Entering a first function... \n");
				c::Enter(&f1);
				system("cls");
				c::Print(f1, "f1");
				printf("Entering a second function... \n");
				c::Enter(&f2);
				system("cls");
				res = c::Sum(f1, f2);
				c::Print(f1, "f1");
				c::Print(f2, "f2");
				c::Print(res, "f");
				system("pause");
				continue;
			}
			else if (value == 2)
			{
				system("cls");
				printf("Entering a first function... \n");
				c::Enter(&f1);
				system("cls");
				c::Print(f1, "f1");
				printf("Entering a second function... \n");
				c::Enter(&f2);
				system("cls");
				res = c::Dif(f1, f2);
				c::Print(f1, "f1");
				c::Print(f2, "f2");
				c::Print(res, "f");
				system("pause");
				continue;
			}
			else if (value == 3)
			{
				system("cls");
				printf("Entering a function... \n");
				c::Enter(&f1);
				system("cls");
				c::Print(f1, "f");
				c::Deriv(&f1);
				c::Print(f1, "f'");
				system("pause");
				continue;
			}
			else if (value == 4)
			{
				system("cls");
				printf("Entering a function... \n");
				c::Enter(&f1);
				system("cls");
				c::Print(f1, "f");
				double x = utils::read_double("Enter a point: ", -DBL_MAX, DBL_MAX, EPS);
				double result = c::Point(f1, x);
				printf("f(%.2lf) = %.2lf\n", x, result);
				system("pause");
				continue;
			}
		}
		else//c++
		{
			cpp::Func f1, f2, res;
			if (value == 1)
			{
				system("cls");
				printf("Entering a first function... \n");
				f1.Enter();
				system("cls");
				f1.Print("f1");
				printf("Entering a second function... \n");
				f2.Enter();
				system("cls");
				res = f1.Sum(f2);
				f1.Print("f1");
				f2.Print("f2");
				res.Print("f");
				system("pause");
				continue;
			}
			else if (value == 2)
			{
				system("cls");
				printf("Entering a first function... \n");
				f1.Enter();
				system("cls");
				f1.Print("f1");
				printf("Entering a second function... \n");
				f2.Enter();
				system("cls");
				res = cpp::Func::StaticDif(f1, f2);
				f1.Print("f1");
				f2.Print("f2");
				res.Print("f");
				system("pause");
				continue;
			}
			else if (value == 3)
			{
				system("cls");
				printf("Entering a function... \n");
				f1.Enter();
				system("cls");
				f1.Print("f");
				f1.Deriv();
				f1.Print("f'");
				system("pause");
				continue;
			}
			else if (value == 4)
			{
				system("cls");
				printf("Entering a function... \n");
				f1.Enter();
				system("cls");
				f1.Print("f");
				double x = utils::read_double("Enter a point: ", -DBL_MAX, DBL_MAX, EPS);
				double result;
				result = f1.Point(x);
				printf("f(%.2lf) = %.2lf\n", x, result);
				system("pause");
				continue;
			}
		}
		system("cls");
	}
}*/