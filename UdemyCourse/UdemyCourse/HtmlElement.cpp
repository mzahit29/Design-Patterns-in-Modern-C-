#include "stdafx.h"

#include "HtmlElement.h"
#include "HtmlBuilder.h"
#include <sstream>

void HtmlElement::add_child(HtmlElement & element)
{
	elements.emplace_back(element);
}

HtmlBuilder HtmlElement::create(string name, string text)
{
	return HtmlBuilder{ name, text };
}

string HtmlElement::str(int spaces) const {
	stringstream result;

	stringstream space_string;
	for (int i = 0; i < spaces; ++i)
	{
		space_string << " ";
	}

	result << space_string.str() << "<" << name_ << ">";
	result << space_string.str() << text_ << endl;
	for (auto &element : elements)
	{
		result << element.str(spaces + 1);
	}
	result << space_string.str() << "</" << name_ << ">" << endl;

	return result.str();
}