#include <cmath>
#include <iostream>
#include <memory>
#include "libutils/bool_func.h"
#include <ctime>
BoolFunc::~BoolFunc()
{
	//if (trace)
		//std::cout << "dtor\n";
	if(this->_value)
		delete[] _value;
	_self_dual = 0;
}
BoolFunc::BoolFunc() 
 {
	 _N = 0;
	 _value = nullptr;
	 _self_dual = 0;
 }
/**/
BoolFunc::BoolFunc(size_t N, bool key) : _N(N), _value(new bool[(size_t)pow(2, _N)]), _self_dual(-1) //ctor param
{
	//if (trace)
		//std::cout << "ctor\n";
	if (N)
		for (size_t i = 0; i < (size_t)pow(2, N); ++i)
			_value[i] = key;
	else
		_value = nullptr;
}
BoolFunc::BoolFunc(const BoolFunc& f1) : _N(f1._N), _value(_value = new bool[(size_t)pow(2, f1._N)]), _self_dual(-1) // ctor copy
{
	////if (trace)
		//std::cout << "ctor-copy\n";
	for (size_t i = 0; i < (size_t)pow(2, _N); ++i)
	{
		_value[i] = f1._value[i];
	}
}
BoolFunc::BoolFunc(BoolFunc&& f1) noexcept : _N(f1._N), _value(f1._value), _self_dual(-1)//ctor �������
{
	//if (trace)
	//	std::cout << "move-ctor\n";
	f1._N = 0;
	f1._value = nullptr;
	f1._self_dual = -1;
}
BoolFunc& BoolFunc::operator=( BoolFunc&& f1) noexcept //=-move
{
	//if (trace)
		//std::cout << "move-assign\n";
	Set_self_dual(-1);
	delete[] _value;
	_value = f1._value;
	_N = f1._N;
	_self_dual = f1._self_dual;
	f1._value = nullptr;
	f1._N = 0;
	f1._self_dual = -1;
	return *this;
}
size_t BoolFunc::Get_N() const noexcept
{
	return _N;
}
void BoolFunc::Set_self_dual(int key)
{
	_self_dual = key;
}
BoolFunc operator +(const BoolFunc &f1,const BoolFunc &f2) 
{
	BoolFunc result(f1);
	result += f2;
	return result;
}
BoolFunc operator*(const BoolFunc &f1,const BoolFunc &f2) 
{
	if (f1.Get_N() != f2.Get_N())
	{
		throw "Different dimensions";
	}
	BoolFunc result(f1.Get_N(), 0);
	for (size_t i = 0; i < (size_t)pow(2, f1.Get_N()); ++i)
		result[i] = f1[i] && f2[i];
	return result;
}
BoolFunc operator!(BoolFunc& f1) noexcept
{
	BoolFunc result(f1.Get_N(), 0);
	for (size_t i = 0; i < (size_t)pow(2, f1.Get_N()); ++i)
		result[i]=!f1[i];
	return result;
}
bool& BoolFunc::operator[](size_t index) const
{
	if (index >= 0 && index < (size_t)pow(2,_N))
		return _value[index];
	else
		throw "Invalid index";
}
bool& BoolFunc::operator[](size_t index)
{
	Set_self_dual(-1);
	if (index >= 0 && index < (size_t)pow(2, _N))
		return _value[index];
	else
		throw "Invalid index";
}
bool& BoolFunc::operator*(size_t pos) const
{
	return *(_value + pos);

}
BoolFunc& BoolFunc::operator=(const BoolFunc &f2) 
{
	//if (trace)
		//std::cout << "copy assign\n";
	Set_self_dual(-1);
	if (f2._value!=nullptr) 
	{
		auto new_value = new bool[(size_t)pow(2, f2._N)];
		for (size_t i = 0; i < (size_t)pow(2, f2._N); ++i)
			new_value[i] = f2._value[i];
		delete[] _value;
		_value = new_value;
	}
	else {
		delete[] _value;
		_value = nullptr;
	}
	_N = f2._N;
	_self_dual = f2._self_dual;
	return *this;
}

BoolFunc& BoolFunc::operator+=(const BoolFunc &f2)
{
	Set_self_dual(-1);
	if (_N != f2.Get_N())
		throw"Different dimensions!";
	for (size_t i = 0; i < (size_t)pow(2, _N); ++i)
	{
		f2[i] += (*this)[i];
	}
	return (*this);
}
BoolFunc& BoolFunc::operator*=(const BoolFunc &f2)
{
	Set_self_dual(-1);
	if (_N != f2.Get_N())
	{
		throw "Different dimensions";
	}
	BoolFunc result = (*this) * f2;
	*this = result;
	return *this;
}
std::ostream& operator<<(std::ostream& out, const BoolFunc& f1) 
{
	for (size_t i = 0; i<(size_t)pow(2, f1.Get_N()); ++i)
	{
		std::cout << f1[i] << " ";
	}
	return (out);
}
size_t From_2_To_10(bool* arr, size_t len)
{

	size_t result=0;
	for (size_t i = len; i > 0; --i)
	{
		if (arr[i - 1]==0||arr[i-1]==1)
			result += (size_t)arr[i - 1] * pow(2, len - i);
		else
			throw"Invalid index";
	}
	return result;
}
bool Calculation(const BoolFunc& f1,  bool* arr, size_t len)
{
	if (len != f1.Get_N())
		throw"Different dimensions";
	int index = From_2_To_10(arr, len);
	return f1[index];
}
bool operator==(const BoolFunc& f1, const BoolFunc& f2)
{
	if (f1.Get_N() != f2.Get_N())
		throw"Different dimensions";
	else
	{
		for (size_t i = 0; i < (size_t)pow(2, f1.Get_N()); ++i)
		{
			if (f1[i] != f2[i])
				return false;
		}
		return true;
	}
}
bool operator!=(const BoolFunc& f1, const BoolFunc& f2)
{
	return !(f1 == f2);
}
bool Is_Constant_true(const BoolFunc& f1) noexcept//T1
{
	for (size_t i = 0; i < (size_t)pow(2, f1.Get_N()); i++)
	{
		if (!f1[i])
			return false;
	}
	return true;
}
bool Is_Constant_false(const BoolFunc& f1) noexcept
{
	for (size_t i = 0; i < (size_t)pow(2, f1.Get_N()); i++)
	{
		if (f1[i])
			return false;
	}
	return true;
}
bool BoolFunc::Is_Self_Dual() const
{
	if(_self_dual==-1)
	{
		for (size_t i = 0; i < (size_t)pow(2, _N)/2; ++i)
		{
			if ((*this)[i] == (*this)[(size_t)pow(2, _N) - i - 1])
			{
				continue;
			}
			else
			{
				_self_dual = 0;
				return false;
			}
		}
		_self_dual = 1;
		return true;
	}
	else if (_self_dual == 0)
		return false;
	else if (_self_dual == 1)
		return true;
}
bool Random_Value()
{
	srand(time(nullptr));
	return rand() % 2;
}