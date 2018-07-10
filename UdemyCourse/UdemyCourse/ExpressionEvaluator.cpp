#include "stdafx.h"
#include "ExpressionEvaluator.h"
#include "Visitor.h"

void ExpressionEvaluator::visit(DoubleExpression* de)
{
	result = de->value_;
}

void ExpressionEvaluator::visit(AdditionExpression* ae)
{
	ae->left_->accept(this);
	auto temp = result;
	ae->right_->accept(this);
	result += temp;
}

double ExpressionEvaluator::evaluate()
{
	return result;
}
