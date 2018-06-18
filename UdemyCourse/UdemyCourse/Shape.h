#pragma once
#include "Renderer.h"

class Shape
{
protected:
	Renderer & renderer_;
	Shape(Renderer & renderer) : renderer_(renderer) {}
public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

class Circle : public Shape
{
	float x_, y_, radius_;
public:
	Circle(Renderer & rr, float x, float y, float radius) : Shape(rr), x_(x), y_(y), radius_(radius) {}

	void draw() override
	{
		renderer_.render_circle(x_, y_, radius_);
	}
	void resize(float factor) override
	{
		radius_ *= factor;
	}
};