#pragma once
#include <iostream>
#include <vector>
#include <ostream>

using namespace std;

class BankAccount
{
	float balance_;
	float minimum_balance_;
public:

	explicit BankAccount(float balance, float minimum_balance)
		: balance_(balance), minimum_balance_(minimum_balance)
	{
	}

	void deposit(float f)
	{
		balance_ += f;
		cout << "Deposited : " << f << " TL "
			<< "Account balance : " << balance_ << endl;
	}
	
	void withdraw(float f)
	{
		if ((balance_- f) > minimum_balance_)
		{
		balance_ -= f;
		cout << "Withdrew : " << f << " TL "
			<< "Account balance : " << balance_ << endl;			
		}
	}


	friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj)
	{
		return os << "balance_: " << obj.balance_;
	}
};

class Command
{
public:
	virtual void call() const = 0;
};

class BankAccountCommand : public Command
{
	BankAccount& ba_;
	float amount;
public:
	enum Action { withdraw, deposit } action_;

	BankAccountCommand(BankAccount& ba, Action action, float amount)
		: ba_(ba),
		  action_(action),
		  amount(amount)
	{
	}

	void call() const override
	{
		switch (action_)
		{
		case withdraw:
			ba_.withdraw(amount);
			break;
		case deposit:
			ba_.deposit(amount);
			break;
		}
	}
};