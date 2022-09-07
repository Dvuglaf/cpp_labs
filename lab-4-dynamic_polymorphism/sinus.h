#pragma once
#include "functions.h"
#include "cosinus.h"
class sinus :virtual public functions
{
	double a;
public:
	std::shared_ptr<functions> derivative() noexcept override;
	double value_point(double) const noexcept override;
	bool equals(const functions&) const noexcept override;
	void print() const noexcept override;
	double get_a() const noexcept;
	sinus(double a_value) : a(a_value) {  }
};