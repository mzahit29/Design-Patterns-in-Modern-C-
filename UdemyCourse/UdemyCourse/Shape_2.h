#pragma once
#include <string>
#include <sstream>

namespace Decorator
{
	class Shape
	{
	public:
		virtual std::string str() = 0;
	};

	class Circle : public Shape
	{
		float radius_;
	public:
		Circle(float radius) : radius_(radius)
		{
		}

		void resize(float factor)
		{
			radius_ *= factor;
		}

		std::string str() override
		{
			std::ostringstream oss;
			oss << "A circle with a radius of " << radius_;
			return oss.str();
		}
	};

	class Square : public Shape
	{
		float side_;
	public:
		Square(float side) : side_(side)
		{
		}

		//void resize(float factor)
		//{
		//	side_ *= factor;
		//}

		std::string str() override
		{
			std::ostringstream oss;
			oss << "A square with a side of " << side_;
			return oss.str();
		}
	};

	// Now we want a colored shape. We will decorate Circle class by using its base class reference. 
	// No change in Circle or Shape is required which conforms to the OCP
	// Also single responsibility is not violated
	class ColoredShape : public Shape
	{
		string color_;
	public:
		Shape& shape_;

		ColoredShape(Shape& shape, string color) : shape_(shape), color_(color)
		{
		}

		std::string str() override
		{
			std::ostringstream oss;
			oss << shape_.str() << " with color " << color_;
			return oss.str();
		}
	};

	class TransparentShape : public Shape
	{
	public:
		Shape& shape_;
		float transparency_;

		TransparentShape(Shape &shape, float transparency) : shape_(shape), transparency_(transparency) {}

		string str() override
		{
			ostringstream oss;
			oss << shape_.str() << " with transparency: " << transparency_;
			return oss.str();
		}
	};
}
