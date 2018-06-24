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
	
	bool withdraw(float f)
	{
		if ((balance_- f) > minimum_balance_)
		{
			balance_ -= f;
			cout << "Withdrew : " << f << " TL "
				<< "Account balance : " << balance_ << endl;
			return true;
		}
		return false;
	}


	friend std::ostream& operator<<(std::ostream& os, const BankAccount& obj)
	{
		return os << "balance_: " << obj.balance_;
	}
};

class Command
{
public:
	bool succeded_;
	virtual void call() = 0;
	virtual void undo() = 0;
};

class BankAccountCommand : public Command
{
public:
	BankAccount & ba_;
	float amount_;
	enum Action { withdraw, deposit } action_;

	BankAccountCommand(BankAccount& ba, Action action, float amount)
		: ba_(ba),
		  action_(action),
		  amount_(amount)
	{
		succeded_ = false;
	}

	void call() override
	{
		switch (action_)
		{
		case withdraw:
			succeded_ = ba_.withdraw(amount_);
			break;
		case deposit:
			ba_.deposit(amount_);
			succeded_ = true;
			break;
		}
	}

	void undo() override
	{
		if (!succeded_) return;

		switch(action_)
		{
		case BankAccountCommand::Action::withdraw:
			ba_.deposit(amount_);
			break;
		case BankAccountCommand::Action::deposit:
			ba_.withdraw(amount_);
			break;
		}
	}
};

// Using composite pattern (using same API i.e. call() and undo())
class CompositeBankAccountCommand : public vector<BankAccountCommand>, Command
{
public:

	CompositeBankAccountCommand(const initializer_list<BankAccountCommand>& items)
		: vector<BankAccountCommand>(items)
	{
	}


	void call() override
	{
		for (auto& item : *this)
		{
			item.call();
		}
	}

	void undo() override
	{
		for (auto it = this->rbegin(); it != this->rend(); ++it)
		{
			it->undo();
		}
	}
};


class DependentCompositeCommand : public CompositeBankAccountCommand
{
public:

	explicit DependentCompositeCommand(const initializer_list<BankAccountCommand>& items)
		: CompositeBankAccountCommand(items)
	{
	}

	void call() override
	{
		bool ok = true;

		for (auto& cmd : *this)
		{
			if (ok)
			{
				cmd.call();
				ok = cmd.succeded_;
			}
			else
			{
				cmd.succeded_ = false;
			}
		}
	}

};

// Used to simulate money transfer, but it has a _bug_ If one operations fails the other should fail as well,
// but it doesn't therefore to correct it instead of inheriting directly from CompositeBankAccountCommand inherit from
// DependentCompositeCommand.
class MoneyTransferCommand : public DependentCompositeCommand
{
public:

	explicit MoneyTransferCommand(
		BankAccount& from,
		BankAccount& to,
		float amount
	) : DependentCompositeCommand(
		{
			BankAccountCommand{ from, BankAccountCommand::Action::withdraw, amount },
			BankAccountCommand{ to, BankAccountCommand::Action::deposit, amount }
		}
	) {}
};