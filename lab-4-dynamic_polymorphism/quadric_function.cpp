#include "quadric_function.h"
#include<memory>
#include <iostream>
std::shared_ptr<functions> quadric_function::derivative() noexcept
{
	return std::make_shared<quadric_function>(quadric_function(0, 2 * a, b));
}
double quadric_function::value_point(double x) const noexcept
{
	return (a * x * x + b * x + c);
}
bool quadric_function::equals(const functions& rhs)const noexcept
{
	auto non_const = const_cast<functions*>(&rhs);

	auto copy = dynamic_cast<quadric_function*>(non_const);

	if (!copy)
		return false;

	if (a == (*copy).a && b == (*copy).b && c == (*copy).c)
		return true;
	return false;
}
void quadric_function::print() const noexcept
{
	if (a != 0)
		std::cout << a << "x^2";
	if (b < 0)
		std::cout << b << "x";
	if (b > 0)
	{
		if (a != 0)
			std::cout << "+";
		std::cout << b << "x";
	}
	if (c < 0)
		std::cout << c;
	if (c > 0)
	{
		if (b != 0)
			std::cout << "+";
		std::cout << c;
	}
	std::cout << "\n";
}