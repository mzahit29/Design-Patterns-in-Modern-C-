#pragma once
#include "ExpressionVisitor.h"

struct ExpressionEvaluator : ExpressionVisitor
{
	double result{};
	void visit(DoubleExpression* de) override;
	void visit(AdditionExpression* ae) override;

	double evaluate();
};

