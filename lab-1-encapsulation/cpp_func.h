namespace cpp 
{
	class Func
	{
	private:
		double _a, _b, _c;
	public:
		Func Sum(const Func&) const;
		Func Dif(const Func&) const;
		void Deriv();
		double Point(double) const;
		void Enter();
		void Print(const char*) const;
		double  Get_a() const;
		double  Get_b() const;
		double  Get_c() const;
		Func() : _a(0), _b(0), _c(0) {};
		Func(double a, double b, double c) : _a(a), _b(b), _c(c) {  };
		void Set_a(double );
		void Set_b(double b);
		void Set_c(double c);
		static Func StaticDif(const Func& , const Func& );
	};
}
