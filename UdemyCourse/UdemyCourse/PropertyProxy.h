#pragma once
#include <iostream>
#include <string>
#include <ostream>
using namespace std;

namespace Proxy
{
	template <typename T>
	class Property
	{
		T value_;
	public:
		Property(const T & value) : value_(value) {}
		operator T() const
		{
			return value_;
		}
		// Note that right hand is of type T not Property, because we will be setting a Property<int> dexterity_; dexterity = 99;
		Property & operator=(const T & value)
		{
			// Do your preferred operations on setting the property
			cout << "Setting property" << endl;
			value_ = value;
			return *this;
		}

	};


	class Creature
	{
	public:
		// Using property proxy for strength_ and agility_
		Property<int> strength_{ 10 };
		Property<int> agility_{ 5 };
		Creature(int strength, int agility) : strength_(strength), agility_(agility) {}
		friend ostream & operator<<(ostream & out, const Creature & obj)
		{
			return out
				<< "Creature strength: " << static_cast<int>(obj.strength_)  // Explicit conversion operator invoked
				<< " agility: " << obj.agility_;  // Implicit conversion to int takes place
		}
	};
}
