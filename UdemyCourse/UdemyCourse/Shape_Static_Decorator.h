#pragma once
#include <string>
using namespace std;


// Static Decorator example	
template <typename T>
class ColoredShape2 : public T
{
	string color_;
public:
	// ColoredShape2<Decorator::Square> colored_square{"red", 4}
	// To be able to pass the parameters in the constructor to each class in the hierarchy we
	// use variadic templates. So "red" will be used by ColoredShape2 and the rest of the argument pack will be 
	// expanded and passed on to the type T we are inheriting from which in our example is a square.
	// So one thing to note is that ColoredShape2 doesn't know what type it is inheriting from. All it knows is
	// to pass the remaining constructor arguments to its base T. And also it knows that this base T has a string str() method.
	template <typename...Args>
	ColoredShape2(const string & color, Args ...args) : T(std::forward<Args>(args)...), color_(color) {}

	string str() override
	{
		ostringstream oss;
		oss << T::str() << " with color " << color_;
		return oss.str();
	}
};

template <typename T>
class TransparentShape2 : public T
{
	float transparency_;
public:
	// TransparentShape2<ColoredShape2<Decorator::Circle>> sq{55, "red", 8};
	// TransparentShape2 constructor consumes the 55 as transparency value and expands the remaining arguments
	// and forwards it to the base type T, which in our example is ColoredShape2.
	template <typename...Args>
	TransparentShape2(float transparency, Args ...args) : T(std::forward<Args>(args)...), transparency_(transparency) {}

	string str() override
	{
		ostringstream oss;
		oss << T::str() << " with transparency " << transparency_;
		return oss.str();
	}
};