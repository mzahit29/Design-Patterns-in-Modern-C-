#pragma once
#include "stdafx.h"
#include <iostream>
#include <typeindex>
#include <map>

using namespace std;


struct GameObject;

inline void collide(GameObject& first, GameObject& second);

// Remember for typeid to work on runtime types the base class needs to be polymorhpic (i.e. at least one virtual func)
struct GameObject
{
	//virtual type_index type() const = 0;
	virtual void collide(GameObject& other)
	{
		::collide(*this, other);
	}
};


// CRTP
template <typename T>
struct GameObjectImpl : GameObject
{
	//type_index type() const override
	//{
	//	return typeid(T);
	//}
};

void spaceship_planet() { cout << "Spaceship lands on planet" << endl; }
void asteroid_planet() { cout << "Asteroid burns up in the atmosphere" << endl; }
void asteroid_spaceship() { cout << "Asteroid hits and destroys the spaceship" << endl; }



struct Planet : GameObjectImpl<Planet> {};
struct Asteroid : GameObjectImpl<Asteroid> {};
struct Spaceship : GameObjectImpl<Spaceship> {};

map<pair<type_index, type_index>, void(*)()> outcomes
{
	{ { typeid(Planet), typeid(Spaceship) }, spaceship_planet},
	{ { typeid(Asteroid), typeid(Planet) }, asteroid_planet},
	{ { typeid(Asteroid), typeid(Spaceship) }, asteroid_spaceship}
};

template <typename T>
struct foo
{
	
};

inline void collide(GameObject& first, GameObject& second)
{
	cout << "collide( " << typeid(first).name() << ", " << typeid(second).name() << " )" << endl;
	auto it = outcomes.find({ typeid(first), typeid(second) });
	if (it == outcomes.end())
	{
		it = outcomes.find({ typeid(second), typeid(first) });
		if (it == outcomes.end())
		{
			cout << "Objects pass each other harmlessly" << endl;
			return;
		}
	}
	it->second();
}