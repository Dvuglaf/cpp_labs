#pragma once
#include "functions.h"
#include <memory>
class constant_function :virtual public functions
{
	double c;
public:
	std::shared_ptr<functions> derivative() noexcept override;
	double value_point(double x) const noexcept override;
	bool equals(const functions&) const noexcept override;
	void print() const noexcept override;
	constant_function(double c_value) : c(c_value) { }
};