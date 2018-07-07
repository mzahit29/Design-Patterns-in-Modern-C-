#pragma once
#include "stdafx.h"
#include <sstream>
#include <vector>

using namespace std;

enum class OutputFormat
{
	markdown,
	html
};

struct ListStrategy
{
	virtual void start(ostringstream & oss) {}
	virtual void add_item(ostringstream & oss, const string & str) {}
	virtual void end(ostringstream & oss) {}
};


struct MarkDownListStrategy : ListStrategy
{
	void add_item(ostringstream& oss, const string& str) override
	{
		oss << "* " << str << "\n";
	}
};

struct HtmlListStrategy : ListStrategy
{
	void start(ostringstream& oss) override
	{
		oss << "<ul>\n";
	}
	void add_item(ostringstream& oss, const string& str) override
	{
		oss << "\t<li> " << str << " </li>\n";
	}
	void end(ostringstream& oss) override
	{
		oss << "</ul>\n";
	}
};

// Dynamic strategy: You can set the list_strategy_ on run time
class TextProcessor
{
	ostringstream oss;
	unique_ptr<ListStrategy> list_strategy_;
public:
	void set_output_format(const OutputFormat & format)
	{
		switch(format) { 
		case OutputFormat::markdown:
			list_strategy_ = make_unique<MarkDownListStrategy>();
			break;
		case OutputFormat::html:
			list_strategy_ = make_unique<HtmlListStrategy>();
			break;
		default: ;
		}
	}

	void clear()
	{
		oss.str("");
		oss.clear();
	}

	void append_list(const vector<string> & items)
	{
		for (auto & item : items)
		{
			list_strategy_->start(oss);
			list_strategy_->add_item(oss, item);
			list_strategy_->end(oss);
		}
	}

	string str()
	{
		return oss.str();
	}
};



// Static strategy: You can NOT set the list_strategy_ on run time, it is set by template parameter statically
template <typename LS>
class TextProcessor_Static
{
	ostringstream oss;
	LS list_strategy_;
public:
	void clear()
	{
		oss.str("");
		oss.clear();
	}

	void append_list(const vector<string> & items)
	{
		for (auto & item : items)
		{
			list_strategy_.start(oss);
			list_strategy_.add_item(oss, item);
			list_strategy_.end(oss);
		}
	}

	string str()
	{
		return oss.str();
	}
};