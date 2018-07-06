#pragma once
#include "stdafx.h"
#include "Observable.h"
#include "Observer.h"
#include <iostream>

using namespace std;

namespace ObserverNS
{
	class Person  : public Observable<Person> // Observable
	{
	public:
		int age_;
		Person(int age) : age_(age) {}


		int age() const
		{
			return age_;
		}

		void set_age(int age)
		{
			if (this->age_ == age) return;
			this->age_ = age;
			notify(*this, "age");
		}
	};


	class PersonObserver : public Observer<Person>
	{
	public:

		void field_changed(Person& source, const string& field_name) override
		{
			cout << "Person's field has changed" << endl;
			if (field_name == "age")
			{
				cout << "age value changed to : " << source.age_ << endl;
			}
		}
	};
}




