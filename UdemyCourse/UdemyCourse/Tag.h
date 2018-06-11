#pragma once
#include <iostream>
#include <string>
#include <vector>

class Tag
{
public:
	
	std::string name_, text_;
	std::vector<Tag> children_;
	std::vector<std::pair<std::string, std::string>> attributes_;



	Tag(const std::string& name, const std::string& text)
		: name_(name),
		  text_(text)
	{
	}


	Tag(const std::string& name, const std::vector<Tag>& children)
		: name_(name),
		  children_(children)
	{
	}

	friend std::ostream & operator<<(std::ostream &out, const Tag & tag)
	{
		out << "<" << tag.name_;

		if (tag.attributes_.size() != 0)
		{
			for (auto &attribute : tag.attributes_)
			{
				std::cout << " " << attribute.first << "=" << attribute.second << " ";
			}
		}


		if (tag.children_.size() == 0 && tag.text_.length() == 0)
		{
			out << "/>";
		}
		else
		{
			out << "> " << tag.text_ << std::endl;
			for (auto &child : tag.children_)
			{
				out << child;
			}
			out << "\n</" << tag.name_ << ">" << std::endl;
		}
		
		return out;
	}
};


class P : public Tag
{
public:
	P(const std::string& text)
		: Tag("p", text)
	{
	}

	P(const std::vector<Tag>& children)
		: Tag("p", children)
	{
	}

	P(std::initializer_list<Tag> children)
		: Tag("p", children)
	{
	}
};

class IMG : public Tag
{
public:
	IMG(const string & url)
		: Tag("img", "")
	{
		attributes_.emplace_back(std::make_pair("src", url));
	}
};