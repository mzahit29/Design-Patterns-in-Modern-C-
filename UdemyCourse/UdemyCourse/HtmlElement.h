#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;
using std::vector;

class HtmlBuilder;

class HtmlElement {
	// We don't want user to create HtmlElement without builder, therefore constructors are private
	HtmlElement() = default;
	explicit HtmlElement(const string &name, const string &text = "") : name_(name), text_(text) {}

	// But we need the builder class to be able construct HtmlElements, for this purpose we make HtmlBuilder friend
	friend class HtmlBuilder;
public:
	string name_;
	string text_;
	vector<HtmlElement> elements;  // Child elements
	
	
	
	void add_child(HtmlElement & element);
	string str(int spaces = 0) const;

	static HtmlBuilder create(string name, string text);
};