#pragma once
#include <iostream>
#include <string>
#include <ostream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
using namespace boost;

using namespace std;


class Address
{
public:
	string city_;
	string street_;
	string number_;

	Address() = default;
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

private:
	friend class serialization::access;

	template <typename archive>
	void serialize(archive & ar, const unsigned version)
	{
		ar & city_;
		ar & street_;
		ar & number_;
	}
};

class Contact_No_Pointers
{
public:
	string name_;
	Address address_;

	Contact_No_Pointers(const string& name, const Address& address)
		: name_(name),
		  address_(address)
	{
	}


	friend std::ostream& operator<<(std::ostream& os, const Contact_No_Pointers& obj)
	{
		return os
			<< "name_: " << obj.name_
			<< " address_: " << obj.address_;
	}
};

class Contact
{
public:
	string name_;
	Address *address_;

	Contact() = default;
	Contact(const string& name, Address* address)
		: name_(name),
		address_(address)
	{
	}

	Contact(const Contact & other)
		: name_(other.name_),
		address_(new Address{*other.address_})
	{
		cout << "Contact(const Contact & other)" << endl;
	}

	~Contact()
	{
		delete address_;
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
	{
		return os
			<< "name_: " << obj.name_
			<< " address_: " << *obj.address_;
	}
private:
	friend class serialization::access;

	template<typename archive>
	void serialize(archive& ar, const unsigned version)
	{
		ar & name_;
		ar & address_;
	}
};