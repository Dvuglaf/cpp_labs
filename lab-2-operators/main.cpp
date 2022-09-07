/*#include <iostream>
#include "bool_func.h"
#include <libutils/io.h>
#include <cstdlib>
extern bool trace = false;
int main()
{
	size_t N1, N2;
	bool value1, value2;
	N1 = utils::read_int("Enter dimension 1: ", 0, 10);
	std::cout << std::endl;
	N2 = utils::read_int("Enter dimension 2: ", 0, 10);
	std::cout << std::endl;
	value1 = (bool)utils::read_int("Enter value1: ", 0, 1);
	std::cout << std::endl;
	value2 = (bool)utils::read_int("Enter value2: ", 0, 1);
	std::cout << std::endl;
	BoolFunc f1(N1, value1), f2(N2, value2),f3(0,0);
	while (1)
	{
		system("cls");
		std::cout << "f1: " << f1 << std::endl;
		std::cout << "f2: " << f2 << std::endl;

		std::cout << "1.+\n2.*\n3.!\n4.[ ]\n5.=\n6.==\n7.!=\n8.+=\n9.*=\n10.Belong to T0. \n11.Belong to T1.\n12.Belong to S;\n13.Calculation(const bool*)\n0.Exit\n";
		int marker = utils::read_int("Enter a number: ", 0, 13);
		if (marker == 0)
			return 0;
		else if (marker == 1)
		{
			try { ::trace = true; f3 = f1+f2; ::trace = false; std::cout << f3; }
			catch (const char* s) { std::cout << s << std::endl; }
		}
		else if (marker == 2)
		{
			try { ::trace = true; f3 = f2 * f1; ::trace = false; std::cout << f3;
			}
			catch (const char* s) {	std::cout << s << std::endl;}		}
		else if (marker == 3)
		{
			::trace = true;
			f1 = !f1;
			std::cout <<"!f1: "<< f1;
			::trace = false;
		}
		else if (marker == 4)
		{
			size_t i = (size_t)utils::read_int("Enter index: ", 0, (int)pow(2, f1.Get_N()));
			bool new_value = (bool)utils::read_int("Enter a new value: ", 0, 1);
			try { f1[i] = new_value; }
			catch (const char* s) { std::cout << s << std::endl; }
		}
		else if (marker == 5)
		{
			f2 = f1;
			std::cout << "f2=f1= " << f2;
		}
		else if (marker == 6)
		{
			try
			{ 
				bool flag = (f1 == f2); 
				std::cout << flag;
			}
			catch (const char* s) { std::cout << s << std::endl; }
		}
		else if (marker == 7)
		{
			try
			{
				bool flag = (f1 != f2);
				std::cout << flag;
			}
			catch (const char* s) { std::cout << s << std::endl; }
		}
		else if (marker == 8)
		{
			try
			{
				::trace = true;
				f1 += f2;
				::trace = false;
				std::cout << f1;
			}
			catch (const char* s) { std::cout << s << std::endl; }
		}
		else if (marker == 9)
		{
			try
			{
				::trace = true;
				f1 *= f2;
				::trace = false;
				std::cout << f1;
			}
			catch (const char* s) { std::cout << s << std::endl; }		
		}
		else if (marker == 10)
		{
			std::cout << Is_Constant_false(f1);
		}
		else if (marker == 11)
		{
			std::cout << Is_Constant_true(f1);
		}
		else if (marker == 12)
		{
			std::cout << f1.Is_Self_Dual();
		}
		else if (marker == 13)
		{
			try 
			{
				int dimension=utils::read_int("Enter a boolean array dimension",1,10);
				bool* arr = new bool[dimension];
				std::cout << "bool arr = ";
				for (size_t i = 0; i < dimension; ++i)
				{
					arr[i] = Random_Value();
					std::cout << arr[i]<<" ";
				}
				std::cout << std::endl;
				std::cout << Calculation(f1, arr, (size_t)dimension);
			}
			catch (const char* s) { std::cout << s << std::endl; }
		}
		std::cout << std::endl;
		system("pause");
	}
}*/