#pragma once
#include "stdafx.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace AcyclicVisitorNS
{
	template <typename Visitable>
	struct Visitor
	{
		virtual void visit(Visitable& obj) = 0;
	};


	struct VisitorBase
	{
		virtual ~VisitorBase() = default;
	};

	struct Expression
	{
		virtual ~Expression() = default;

		// Accepting a marker interface
		//                               vvv Visitor<T> is expected, so try casting it with dynamic_cast and work on it if succeeds.
		virtual void accept(VisitorBase& obj)
		{
			using EV = Visitor<Expression>;
			if(auto ev = dynamic_cast<EV*>(&obj))
			{
				ev->visit(*this);
			}
		}
	};


	struct DoubleExpression : Expression
	{
		double value_;

		DoubleExpression(double value) : value_(value) {}

		virtual void accept(VisitorBase& obj) override
		{
			using DEV = Visitor<DoubleExpression>;
			if(auto dev = dynamic_cast<DEV*>(&obj))
			{
				dev->visit(*this);
			}
		}
	};

	struct AdditionExpression : Expression
	{
		Expression *left_, *right_;


		AdditionExpression(Expression* left, Expression* right)
			: left_(left),
			  right_(right) {}

		~AdditionExpression()
		{
			delete left_;
			delete right_;
		}

		virtual void accept(VisitorBase& obj) override
		{
			using AEV = Visitor<AdditionExpression>;
			if (auto aev = dynamic_cast<AEV*>(&obj))
			{
				aev->visit(*this);
			}
		}
	};

	struct ExpressionPrinter : VisitorBase, 
								 Visitor<DoubleExpression>,
								 Visitor<AdditionExpression>
	{
		void visit(DoubleExpression& obj) override
		{
			oss << obj.value_;
		}
		void visit(AdditionExpression& obj) override
		{
			oss << "(";
			obj.left_->accept(*this);
			oss << "+";
			obj.right_->accept(*this);
			oss << ")";
		}

		string str() { return oss.str(); }

	private:
		ostringstream oss;
	};


	struct ExpressionEvaluator : VisitorBase,
									Visitor<DoubleExpression>,
									Visitor<AdditionExpression>
	{
		void visit(DoubleExpression& obj) override
		{
			result = obj.value_;
		}

		void visit(AdditionExpression& obj) override
		{
			obj.left_->accept(*this);
			auto temp = result;
			obj.right_->accept(*this);
			result += temp;
		}

		double evaulate() { return result; }
	private:
		double result{};
	};

}
