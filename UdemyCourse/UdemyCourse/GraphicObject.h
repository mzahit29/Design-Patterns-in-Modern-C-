#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class GraphicObject
{
public:
	virtual void draw() = 0;
};

class CircleGraphic : public GraphicObject
{
public:
	void draw() override
	{
		cout << "Drawing circle" << endl;
	}
};

class SquareGraphic : public GraphicObject
{
public:
	void draw() override
	{
		cout << "Drawing square" << endl;
	}
};

class Group : public GraphicObject
{
	vector<GraphicObject *> obj_list;
	string name_;
public:
	Group(const string & name) : name_(name) {}

	void draw() override
	{
		cout << "Drawing group " << name_ << endl;
		for(auto &obj : obj_list)
		{
			obj->draw();
		}
	}

	void add(GraphicObject * obj)
	{
		obj_list.push_back(obj);
	}
};