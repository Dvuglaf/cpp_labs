#pragma once
#include "functions.h"
class quadric_function :virtual public functions
{
	double a, b, c;
public:

	std::shared_ptr<functions> derivative() noexcept override;
	double value_point(double) const noexcept override;
	bool equals(const functions&) const noexcept override;
	void print() const noexcept override;
	quadric_function(double a_value, double b_value, double c_value) :a(a_value), b(b_value), c(c_value) { }
	//~quadric_function() { delete a, b, c; }


};