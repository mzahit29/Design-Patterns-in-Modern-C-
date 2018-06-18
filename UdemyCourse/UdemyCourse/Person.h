#pragma once
#include <string>
using namespace std;

class Person
{
public:
	string name_;
	Person(const string & name);
	~Person();

	// This class is declared here inside Person but it's definition is in Person.cpp file.
	class PersonImpl;
	PersonImpl * pImpl;

	// API consumer only knows about this Person::greet(), the internal PersonImpl::greet() is hidden
	void greet();
};