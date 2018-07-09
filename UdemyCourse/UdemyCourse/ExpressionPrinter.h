#pragma once
#include "stdafx.h"
#include "Visitor.h"


// The following approach won't work because at compile time you have to determine which print will be called. But with
// print(Expression *e, ostringstream& oss) you don't know what e is pointing to.
//class ExpressionPrinter
//{
//	void print(DoubleExpression *de, ostringstream& oss)
//	{
//		oss << de->value_;
//	}
//
//	void print(AdditionExpression *ae, ostringstream& oss)
//	{
//		oss << "(";
//		print(ae->left_, oss);	// This won't work because left_ is a pointer to Expression and there is no overload 
//			// of void print(Expression *exp, ostringstream& oss)
//		oss << "+";
//		print(ae->right_, oss);	// This won't work either for the same reason
//		oss << ")";
//	}
//};

// SECOND APPROACH
class ExpressionPrinter
{
	ostringstream oss;
public:
	void print(Expression *e)
	{
		if (const auto de = dynamic_cast<DoubleExpression*>(e))
		{
			oss << de->value_;
		}
		else if (const auto ae = dynamic_cast<AdditionExpression*>(e))
		{
			oss << "(";
			print(ae->left_);
			oss << "+";
			print(ae->right_);
			oss << ")";
		}
	}

	string str()
	{
		return oss.str();
	}
};

