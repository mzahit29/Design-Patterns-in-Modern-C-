#pragma once
#include <cmath>
#include <iostream>

class Point
{
	friend class PointFactory;  // This violates the Open-Closed Principle, since we are changing Point class to be able to use this factory.
								// There is a second option of making everything public to avoid the friend class.
								// There is a third option of making PointFactory an inner class.
	Point(float x, float y) : x_(x), y_(y) {}
public:
	float x_, y_;

	friend std::ostream & operator<<(std::ostream & out, const Point & p)
	{
		out << "x: " << p.x_ << " y: " << p.y_ << std::endl;
		
		return out;
	}
};