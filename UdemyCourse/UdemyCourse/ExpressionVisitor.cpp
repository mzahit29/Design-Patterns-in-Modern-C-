#include "stdafx.h"
#include "ExpressionVisitor.h"
#include "Visitor.h"

void ExprPrinter::visit(DoubleExpression* de)
{
	oss << de->value_;
}

void ExprPrinter::visit(AdditionExpression* ae)
{
	oss << "(";
	ae->left_->accept(this); // By doing this we are passing the type information of ae->left to the visitor. 
	// visitor->visit(this) is called by the visited object. "this" pointer of the visited object is either DoubleExpression
	// or AdditionExpression. Compiler calls the appropriate visit method o ExprPrinter according to pointer type. 
	// Inside the visit method the data from the visited object is handled (i.e. printed in this example)
	oss << "+";
	ae->right_->accept(this);
	oss << ")";
}

string ExprPrinter::str()
{
	return oss.str();
}
