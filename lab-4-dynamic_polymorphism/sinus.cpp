#include "sinus.h"
#include "cosinus.h"
#include <cmath>
#include <iostream>
std::shared_ptr<functions> sinus::derivative() noexcept
{
	return std::make_shared<cosinus>(cosinus(a));
}
double sinus::value_point(double x)const noexcept
{
	return a*sin(x);
}
bool sinus::equals(const functions& rhs) const noexcept
{
	auto nonConst = const_cast<functions*>(&rhs);
	auto copy = dynamic_cast<sinus*>(nonConst);
	if (!copy)
		return false;
	if (a==(*copy).a)
		return true;
	return false;
}
void sinus::print() const noexcept
{
		std::cout << a << "sin(x)\n";
}
double sinus::get_a() const noexcept
{
	return a;
}