#pragma once
#include <iostream>
using namespace std;

class Renderer
{
public:
	virtual void render_circle(float x, float y, float radius) = 0;
};


class RasterRenderer : public Renderer
{
public:
	void render_circle(float x, float y, float radius) override
	{
		cout << "Raster rendering circle: " << "x: " << x << " y: " << y << " radius: " << radius << endl;
	}
};

class VectorRenderer : public Renderer
{
public:
	void render_circle(float x, float y, float radius) override
	{
		cout << "Vector rendering circle: " << "x: " << x << " y: " << y << " radius: " << radius << endl;
	}
};
