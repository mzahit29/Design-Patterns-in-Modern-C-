#pragma once
#include "Point.h"
#include <cmath>

class PointFactory
{
public:
	static Point NewPolar(float r, float theta)
	{
		return Point{ r * cos(theta), r * sin(theta) };
	}

	static Point NewCartesian(float x, float y)
	{
		return Point{ x, y };
	}
};