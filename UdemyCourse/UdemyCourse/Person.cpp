#include "stdafx.h"
#include "Person.h"
#include <iostream>

class Person::PersonImpl
{
public:
	void greet(Person *p);
};

// This is the hidden implementation of the greet. It is not visible in the header file. Therefore these details are
// not shipped to the consumer. Also consumer's code doesn't have to change if you change the PersonImpl::greet(..).
void Person::PersonImpl::greet(Person* p)
{
	cout << "Hello " << p->name_ << endl;
}


Person::Person(const string & name) : name_(name), pImpl(new PersonImpl()) {}

Person::~Person()
{
	delete pImpl;
}

void Person::greet()
{
	pImpl->greet(this);
}
