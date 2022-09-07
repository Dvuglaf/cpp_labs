namespace c
{
	struct func  // ax^2+bx+c
	{
		double a, b, c;
	};
	func Sum(func f1, func f2);
	func Sum(func f1, func f2);
	func Dif(func f1, func f2);
	void Deriv(func* f1);
	double Point(func f1, double x);
	void Enter(func* f1);
	void Print(func f1, const char* name);
}

