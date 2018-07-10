#pragma once
#include "stdafx.h"
#include "ExpressionVisitor.h"
#include <iostream>

using namespace std;

class Expression
{
public:
	virtual ~Expression() = default;
	virtual void accept(ExpressionVisitor *visitor) = 0;
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

	void accept(ExpressionVisitor* visitor) override
	{
		visitor->visit(this);
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


	void accept(ExpressionVisitor *visitor) override
	{
		visitor->visit(this);
	}
};