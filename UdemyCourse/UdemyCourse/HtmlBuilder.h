#pragma once
#include <string>
//#include "HtmlElement.h"

using std::string;

class HtmlElement;

class HtmlBuilder
{

public:
	HtmlElement root_;

	HtmlBuilder(string name, string text)
	{
		root_.name_ = name;
		root_.text_ = text;
	}

	HtmlBuilder & add_child(string child_name, string child_text)
	{
		HtmlElement child{child_name, child_text};
		root_.add_child(child);
		return *this;
	}

	string str() const
	{
		return root_.str();
	}
};