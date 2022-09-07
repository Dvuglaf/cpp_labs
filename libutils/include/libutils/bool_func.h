#pragma once
#include <cmath>
	class BoolFunc
	{
		std::size_t _N;
		bool* _value;
		mutable int _self_dual;
	public:
		BoolFunc();
		BoolFunc(std::size_t, bool);//ctor par
		BoolFunc(const BoolFunc&);//ctor copy
		BoolFunc(BoolFunc&& f1) noexcept;//ctor mov.
		~BoolFunc();//dctor
		std::size_t Get_N() const noexcept;
		bool& operator*(size_t pos) const;
		bool& operator[](size_t) const;
		bool& operator[](size_t);
		void Set_self_dual(int);
		BoolFunc& operator= (const BoolFunc&);//=
		BoolFunc& operator+= (const BoolFunc&);//+=
		BoolFunc& operator*= (const BoolFunc&);//*=
		BoolFunc& operator=(BoolFunc&&) noexcept;// = mov.
		bool Is_Self_Dual() const;//belong S
	};
	BoolFunc operator+(const BoolFunc&,const BoolFunc&);//+
	BoolFunc operator*(const BoolFunc&,const BoolFunc&);//*
	BoolFunc operator!(BoolFunc&) noexcept;//!
	bool operator == (const BoolFunc&, const BoolFunc& );//==
	bool operator!=(const BoolFunc& , const BoolFunc& );
	std::ostream& operator<< (std::ostream&, const BoolFunc&);//<<
	bool Calculation(const BoolFunc &, bool* , size_t );//calculation using const bool*
	size_t From_2_To_10(bool* , size_t );//  2---->10
	bool Is_Constant_true(const BoolFunc& )noexcept;//belong T1
	bool Is_Constant_false(const BoolFunc& f1)noexcept;//belong T0
	bool Random_Value();





