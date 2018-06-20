#pragma once
#include <string>
#include <cstdint>
#include <boost/bimap.hpp>
#include <ostream>


using namespace std;
using namespace boost::bimaps;

typedef uint32_t key;

class User
{
private:
	key last_name_, first_name_;
public:
	User(const string& first_name, const string& last_name)
		: first_name_{ add(first_name) },
		last_name_{ add(last_name) } {}

protected:
	static bimap<key, string> names_;
	static key seed_;

	static key add(const string & s)
	{
		auto it = names_.right.find(s);
		// If name is not found in dictionary names_
		if (it == names_.right.end())
		{
			key id = ++seed_;
			names_.insert(bimap<key, string>::value_type(id, s));
			return id;
		} 
		else
		{
			return it->second;
		}
	}

public:
	const string& get_first_name() const
	{
		return names_.left.find(first_name_)->second;
	}
	const string& get_last_name() const
	{
		return names_.left.find(last_name_)->second;
	}


	friend std::ostream& operator<<(std::ostream& os, const User& obj)
	{
		return os
			<< "last_name_: [" << obj.last_name_ << "] - " << obj.get_last_name()
			<< " first_name_: [" << obj.first_name_ << "] - " << obj.get_first_name();
	}
};

key User::seed_{ 0 };
bimap<key, string> User::names_{};