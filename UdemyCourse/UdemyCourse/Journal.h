#pragma once
#include <iostream>
#include <string>
#include <vector>

class journal
{
	std::string title_;
	std::vector<std::string> entries_;
	static int count_;
	
public:
	explicit journal(const std::string & title) : title_(title)
	{
	}

	void add(const std::string & entry)
	{
		entries_.push_back(std::to_string(++count_) + ": " + entry);
	}

	const std::vector<std::string> & get_entries() const
	{
		return entries_;
	}

	friend std::ostream & operator<<(std::ostream & out, const journal & obj)
	{
		for (auto &x : obj.entries_)
		{
			std::cout << x << std::endl;
		}
		return out;
	}
};