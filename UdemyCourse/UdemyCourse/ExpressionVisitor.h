#pragma once
#include "stdafx.h"
#include <sstream>
class AdditionExpression;
class DoubleExpression;
using namespace std;



struct ExpressionVisitor
{
	virtual void visit(DoubleExpression *de) = 0;
	virtual void visit(AdditionExpression *ae) = 0;
};


struct ExprPrinter : ExpressionVisitor
{
	ostringstream oss;
	void visit(DoubleExpression* de) override;
	void visit(AdditionExpression* ae) override;
	string str();
};



