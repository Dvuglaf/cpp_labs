#include "functions.h"
#include "constant_function.h"
#include <iostream>
std::shared_ptr<functions> constant_function::derivative() noexcept
{
	return std::make_shared<constant_function>(constant_function(0));

}
double constant_function::value_point(double x) const noexcept
{
	return c;
}
bool constant_function::equals(const functions& rhs) const noexcept
{
	auto nonConst = const_cast<functions*>(&rhs);
	auto copy = dynamic_cast<constant_function*>(nonConst);
	if (!copy)
		return false;
	if (c == (*copy).c)
		return true;
	return false;
}
void constant_function::print()const noexcept
{
	std::cout << c << "\n";
}