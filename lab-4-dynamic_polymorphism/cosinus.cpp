#include "sinus.h"
#include "cosinus.h"
#include <cmath>
#include <iostream>
#include <memory>
std::shared_ptr<functions> cosinus::derivative() noexcept
{
	return std::make_shared<sinus>(sinus(-a));
}
double cosinus::value_point(double x)const noexcept
{
	return a*cos(x);
}
bool cosinus::equals(const functions& rhs) const noexcept
{
	auto nonConst = const_cast<functions*>(&rhs);
	auto copy = dynamic_cast<cosinus*>(nonConst);
	if (!copy)
		return false;
	if (a == (*copy).a)
		return true;
	return false;
}
void cosinus::print() const noexcept
{
	std::cout << a << "cos(x)\n";
}
double cosinus::get_a() const noexcept
{
	return a;
}
