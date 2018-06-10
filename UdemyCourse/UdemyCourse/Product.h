#pragma once
#include <iostream>
#include <string>

enum class color {red, green, blue};
enum class size {large, medium, small};

class product
{
public:
	std::string name_;
	color color_;
	size size_;

	explicit product(const std::string & name, color c = color::blue, size s = size::medium) : name_(name), color_(c), size_(s) {}

	friend std::ostream & operator<<(std::ostream &out, const product &pr)
	{
		out << pr.name_ << std::endl;
		return out;
	}

};