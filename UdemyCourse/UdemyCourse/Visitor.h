#pragma once
#include "stdafx.h"
#include <sstream>
using namespace std;

class Expression
{
public:
	virtual ~Expression() = default;
};

class DoubleExpression : public Expression
{
public:
	double value_;
	explicit DoubleExpression(double value) : value_(value) {}
	virtual ~DoubleExpression()
	{
		cout << "~DoubleExpression()" << endl;
	}
};

class AdditionExpression : public Expression
{
public:
	Expression *left_{ nullptr }, *right_{ nullptr };
public:
	explicit AdditionExpression(Expression *left, Expression *right) : left_(left), right_(right) {}

	virtual ~AdditionExpression()
	{
		cout << "~AdditionExpression()" << endl;
		delete left_;
		delete right_;
	}
};