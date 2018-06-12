#pragma once
#include <map>
#include "HotDrinkFactory.h"

using namespace std;

// This is a concrete class that has a map of factories
class DrinkFactoryMap
{
public:
	DrinkFactoryMap()
	{
		factory_map["Coffee"] = make_unique<CoffeFactory>();
		factory_map["Tea"] = make_unique<TeaFactory>();
	}
	map<string, unique_ptr<HotDrinkFactory>> factory_map;
};