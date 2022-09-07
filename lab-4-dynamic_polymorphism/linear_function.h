#pragma once
#include "functions.h"

class linear_function :virtual public functions
{
	double b, c;
public:
	std::shared_ptr<functions> derivative() noexcept override;
	double value_point(double) const noexcept override;
	bool equals(const functions&) const noexcept override;
	void print() const noexcept override;
	linear_function(double b_value, double c_value) : b(b_value), c(c_value) { }
};