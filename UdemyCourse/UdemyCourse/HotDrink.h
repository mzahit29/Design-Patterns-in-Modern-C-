#pragma once
#include <iostream>

using namespace std;

class HotDrink
{
public:
	virtual ~HotDrink() = default;
	virtual void prepare() = 0;
};


class Tea : public HotDrink
{
public:
	Tea() { cout << "Tea()" << endl; }
	~Tea() { cout << "~Tea()" << endl; }
	void prepare() override
	{
		cout << "Preparing Tea" << endl;
	}
};


class Coffee : public HotDrink
{
public:
	Coffee() { cout << "Coffee()" << endl; }
	~Coffee() { cout << "~Coffee()" << endl; }
	void prepare() override
	{
		cout << "Preparing Coffee" << endl;
	}
};