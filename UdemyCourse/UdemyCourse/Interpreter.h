#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Token
{
public:
	enum Type { plus, minus, lparen, rparen, integer} type_;

	string text;

	Token(Type type, const string& text)
		: type_(type),
		  text(text)
	{
	}

	friend std::ostream& operator<<(std::ostream& os, const Token& obj)
	{
		return os << "`" << obj.text << "`";
	}
};


vector<Token> lex(const string & text)
{
	vector<Token> result;

	for(int i = 0; i < text.size(); ++i)
	{
		switch(text[i])
		{
		case '(':
			result.push_back(Token{ Token::Type::lparen, "(" });
			break;
		case ')':
			result.push_back(Token{ Token::Type::rparen, ")" });
			break;
		case '+':
			result.push_back(Token{ Token::Type::plus, "+" });
			break;
		case '-':
			result.push_back(Token{ Token::Type::minus, "-" });
			break;
		default:
			ostringstream buffer;
			buffer << text[i];
			for (int j = i + 1; j < text.size(); ++j)
			{
				if (isdigit(text[j]))
				{
					buffer << text[j];
					++i;
				}
				else
				{
					result.push_back(Token{ Token::Type::integer, buffer.str() });
					break;
				}
			}
			break;
		}
	}

	return result;
}