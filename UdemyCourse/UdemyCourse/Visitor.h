#pragma once
#include "stdafx.h"
#include <sstream>
using namespace std;

class Expression
{
public:
	virtual ~Expression() = default;
	virtual void print(ostringstream& oss) = 0;
};

class DoubleExpression : public Expression
{
	double value_;
public:
	explicit DoubleExpression(double value) : value_(value) {}
	virtual ~DoubleExpression()
	{
		cout << "~DoubleExpression()" << endl;
	}

	void print(ostringstream& oss) override
	{
		oss << value_;
	}
};

class AdditionExpression : public Expression
{
	Expression *left_{ nullptr }, *right_{ nullptr };
public:
	explicit AdditionExpression(Expression *left, Expression *right) : left_(left), right_(right) {}

	void print(ostringstream& oss) override
	{
		oss << "(";
		if(left_) left_->print(oss);	// oss object is the visitor, it is visiting each object in the hierarchy of Expressions and accumulating some data from that part
		oss << "+";
		if (right_) right_->print(oss);
		oss << ")";
	}

	virtual ~AdditionExpression()
	{
		cout << "~AdditionExpression()" << endl;
		delete left_;
		delete right_;
	}
};