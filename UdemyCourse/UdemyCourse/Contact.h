#pragma once
#include <iostream>
#include <string>
#include <ostream>

using namespace std;


class Address
{
public:
	string city_;
	string street_;
	string number_;


	Address(const string& city, const string& street, const string& number)
		: city_(city),
		  street_(street),
		  number_(number)
	{
	}

	Address(const Address & other) 
		: city_(other.city_), street_(other.street_), number_(other.number_)
	{}

	friend std::ostream& operator<<(std::ostream& os, const Address& obj)
	{
		return os
			<< "city_: " << obj.city_
			<< " street_: " << obj.street_
			<< " number_: " << obj.number_;
	}
};

class Contact
{
public:
	string name_;
	Address address_;

	Contact(const string& name, const Address& address)
		: name_(name),
		  address_(address)
	{
	}


	friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
	{
		return os
			<< "name_: " << obj.name_
			<< " address_: " << obj.address_;
	}
};

class Contact_With_Pointer
{
public:
	string name_;
	Address *address_;


	Contact_With_Pointer(const string& name, Address* address)
		: name_(name),
		address_(address)
	{
	}

	Contact_With_Pointer(const Contact_With_Pointer & other)
		: name_(other.name_),
		address_(new Address{*other.address_})
	{
		cout << "Contact_With_Pointer(const Contact_With_Pointer & other)" << endl;
	}

	~Contact_With_Pointer()
	{
		delete address_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact_With_Pointer& obj)
	{
		return os
			<< "name_: " << obj.name_
			<< " address_: " << *obj.address_;
	}
};