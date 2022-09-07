#include "functions.h"
#include "quadric_function.h"
#include "linear_function.h"
#include "constant_function.h"
#include "sinus.h"
#include "cosinus.h"
#include <iostream>
#include <libutils/io.h>
#include <cstdlib>
#include <vector>
#include <ctime>
#include<algorithm>
#include <cfloat>
bool cmp(const double& lhs, const double& rhs)
{
	if(lhs < rhs)
		return true;
	return false;
}
void std_cmp(std::vector<std::shared_ptr<functions>>& collection,double x)
{
	auto begin = collection.begin();
	auto end = collection.end();
	std::vector<double> temp_collection;
	while (begin != end)
	{
		temp_collection.push_back( (*begin)->derivative()->value_point(x));
		++begin;
	}
	auto temp = temp_collection.begin();
	auto min = std::min_element(temp_collection.begin(), temp_collection.end(), cmp);
	auto dis = std::distance(temp_collection.begin(), min);
	begin = collection.begin();
	for (int i = 0; i < dis; ++i)
	{
		++begin;
	}
	(*begin)->print();
	(*begin)->derivative()->print();
	std::cout << (*begin)->derivative()->value_point(x) << "\n";
}
void my_cmp(std::vector<std::shared_ptr<functions>>& collection, double x)
{
	auto begin = collection.begin();
	auto end = collection.end();
	auto min = begin;
	while (begin != end)
	{
		if (((*begin)->derivative())->value_point(x) < ((*min)->derivative())->value_point(x))
			min = begin;
		++begin;
	}
	(*min)->print();
	(*min)->derivative()->print();
	std::cout << (*min)->derivative()->value_point(x) << "\n";
}

struct Container {
	~Container() {
		std::cout << "~Container" << std::endl;
	}
};

struct A {
	~A() {
		std::cout << "~A" << std::endl;
	}
};

struct B : public A{
	virtual ~B() {
		std::cout << "~B" << std::endl;
	}
};

/*int main()
{
	{
		A* ptr = new B;
		delete ptr;
	}


	srand(time(NULL));
	std::vector<std::shared_ptr<functions>> collection;
	while (true)
	{
	
		//system("cls");
		std::cout << "1.Create a new function\n2.Insert to the end of collection\n3.Delete an object\n4.Delete a collection\n5.Equality of 2 objects\n6.Print a collection\n7.Function with min. value of derivative\n0.Exit\n";
		int marker = utils::read_int("Enter: ", 0, 7);
		if (marker == 1)
		{
			system("cls");
			int pos = utils::read_int("Enter a position: ", 0, (int)collection.size());
			std::cout << "\n";
			std::vector<std::shared_ptr<functions>>::iterator position = collection.begin();
			for (int i = 0; i < pos; ++i)
				++position;
			std::cout << "1.Quadric\ta*x^2 + b*x + c\n2.Linear\tb*x + c\n3.Constant\tc\n4.Sin(x)\ta*sinx\n5.Cos(x)\ta*cosx\n0.Back\n";
			long key = utils::read_int("Enter a function: ", 0, 5);
			std::cout << "\n";
			if (key == 1)
			{
				double a = utils::read_double("Enter a : ", -DBL_MAX, DBL_MAX, 0.0001);
				double b = utils::read_double("Enter b : ", -DBL_MAX, DBL_MAX, 0.0001);
				double c = utils::read_double("Enter c : ", -DBL_MAX, DBL_MAX, 0.0001);
				collection.insert(position, std::make_shared<quadric_function>(quadric_function(a, b, c)));
			}
			else if (key == 2)
			{
				double b = utils::read_double("Enter b : ", -DBL_MAX, DBL_MAX, 0.0001);
				double c = utils::read_double("Enter c : ", -DBL_MAX, DBL_MAX, 0.0001);
				collection.insert(position, std::make_shared<linear_function>(linear_function(b, c)));
			}
			else if (key == 3)
			{
				double c = utils::read_double("Enter c : ", -DBL_MAX, DBL_MAX, 0.0001);
				collection.insert(position, std::make_shared<constant_function>(constant_function(c)));
			}
			else if (key == 4)
			{
				double a = utils::read_double("Enter a : ", -DBL_MAX, DBL_MAX, 0.0001);
				collection.insert(position, std::make_shared<sinus>(sinus(a)));


			}
			else if (key == 5)
			{
				double a = utils::read_double("Enter a : ", -DBL_MAX, DBL_MAX, 0.0001);
				collection.insert(position, std::make_shared<cosinus>(cosinus(a)));
			}
			else
				continue;
		}
		else if (marker == 2)
		{
			system("cls");
			int number = utils::read_int("Enter a number of objects: ", 0, 10);
			std::cout << "\n";

			for (int i = 0; i < number; ++i)
			{
				int obj = rand() % 5 + 1;
				if (obj == 1)
				{
					double a = (double)(rand() % 20) - 10.;
					double b = (double)(rand() % 20) - 10.;
					double c = (double)(rand() % 20) - 10.;
					collection.push_back(std::make_shared<quadric_function>(quadric_function(a, b, c)));
				}
				else if (obj == 2)
				{
					double b = (double)(rand() % 20) - 10.;
					double c = (double)(rand() % 20) - 10.;
					collection.push_back(std::make_shared<linear_function>(linear_function(b, c)));
				}
				else if (obj == 3)
				{
					double c = (double)(rand() % 20) - 10.;
					collection.push_back(std::make_shared<constant_function>(constant_function(c)));
				}
				else if (obj == 4)
				{
					double a = (double)(rand() % 20) - 10.;
					collection.push_back(std::make_shared<sinus>(sinus(a)));

				}
				else if (obj == 5)
				{
					double a = (double)(rand() % 20) - 10.;
					collection.push_back(std::make_shared<cosinus>(cosinus(a)));

				}
			}
		}
		else if (marker == 3)
		{
			system("cls");
			if (collection.size() == 0)
				std::cout << "Collection is empty!\n";
			int pos = utils::read_int("Enter a position: ", 0, (int)collection.size());	
			std::cout << "\n";
			std::vector<std::shared_ptr<functions>>::iterator position = collection.begin();
			for (int i = 0; i < pos; ++i)
				++position;
			collection.erase(position);
		}
		else if (marker == 4)
		{
			collection.clear();
		}
		else if (marker == 5)
		{
			system("cls");
			int pos_first = utils::read_int("Enter a first index: ", 0, (int)collection.size()-1);
			std::cout << "\n";
			int pos_second = utils::read_int("Enter a second index: ", 0, (int)collection.size()-1);
			std::cout << "\n";
			auto it_first = collection.begin();
			auto it_second = collection.begin();
			for (int i = 0; i < pos_first; ++i)
				++it_first;
			for (int i = 0; i < pos_second; ++i)
				++it_second;
			bool equals = (*it_first)->equals(*(*(it_second)));
			if (equals)
			{
				(*it_first)->print();
				std::cout << "is equal to \n"; 
				(*it_second)->print();
			}
			else
			{
				(*it_first)->print();
				std::cout << " is NOT equal to \n";
				(*it_second)->print();
			}
			std::cout << "\n";
			system("pause");
		}
		else if (marker == 6)
		{
		std::vector<std::shared_ptr<functions>>::iterator it = collection.begin();
		if (collection.size() > 10)
			{
				for (int i = 0; i < 10; ++i)
				{
					(*it)->print();
					++it;
				}
				std::cout << "...\n";
			}
			else
				for (int i = 0; i < collection.size(); ++i)
				{
					(*it)->print();
					++it;
				}
			system("pause");
		}
		else if (marker == 7)
		{
			double x = utils::read_double("Enter a point \"x\": ", -DBL_MAX, DBL_MAX, 0.0001);
			my_cmp(collection, x);
			std_cmp(collection, x);
			system("pause");
		}
		else
			return 0;
	}
}*/