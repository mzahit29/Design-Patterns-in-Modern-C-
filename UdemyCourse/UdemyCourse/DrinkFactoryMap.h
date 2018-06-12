#pragma once
#include <map>
#include <functional>
#include "HotDrinkFactory.h"

using namespace std;

// This is a concrete class that has a map of factories
class DrinkFactoryMap
{
	map<string, unique_ptr<HotDrinkFactory>> factory_map;
public:
	DrinkFactoryMap()
	{
		factory_map["Coffee"] = make_unique<CoffeFactory>();
		factory_map["Tea"] = make_unique<TeaFactory>();
	}
	unique_ptr<HotDrink> make_drink(const string& name)
	{
		auto drink = factory_map[name]->make();
		drink->prepare();
		return drink;
	}
};

class DrinkFactoryFunctionalMap
{
	map<string, function<unique_ptr<HotDrink>()>> factory_function_map;
public:
	DrinkFactoryFunctionalMap()
	{
		factory_function_map["Coffee"] = []()
		{
			unique_ptr<HotDrink> drink = make_unique<Coffee>();
			drink->prepare();
			return drink;
		};

		factory_function_map["Tea"] = []()
		{
			unique_ptr<HotDrink> drink = make_unique<Tea>();
			drink->prepare();
			return drink;
		};
	}

	unique_ptr<HotDrink> make_drink(const string &name)
	{
		return factory_function_map[name]();
	}
};