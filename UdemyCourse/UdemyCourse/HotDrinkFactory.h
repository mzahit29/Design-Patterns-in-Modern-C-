#pragma once
#include <memory>
#include "HotDrink.h"

using namespace std;

class HotDrinkFactory
{
public:
	virtual ~HotDrinkFactory() = default;
	virtual unique_ptr<HotDrink> make() = 0;
};

class TeaFactory : public HotDrinkFactory
{
public:
	unique_ptr<HotDrink> make() override
	{
		return make_unique<Tea>();
	}
};

class CoffeFactory : public HotDrinkFactory
{
public:
	unique_ptr<HotDrink> make() override
	{
		return make_unique<Coffee>();
	}
};