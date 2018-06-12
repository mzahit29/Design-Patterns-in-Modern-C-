#pragma once
#include <cmath>
#include <iostream>

class Point
{
	Point(float x, float y) : x_(x), y_(y) {}
public:
	float x_, y_;

	// Static factory method that creates the Point object using the private constructor
	static Point NewPolar(float r , float theta)
	{
		return Point{ r * cos(theta), r * sin(theta) };
	}

	// Static factory method that creates the Point object using the private constructor
	static Point NewCartesian(float x, float y)
	{
		return Point{ x, y };
	}

	friend std::ostream & operator<<(std::ostream & out, const Point & p)
	{
		out << "x: " << p.x_ << " y: " << p.y_ << std::endl;
		
		return out;
	}

};