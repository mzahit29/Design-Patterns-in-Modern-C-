#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;

namespace Memento
{
	class BankAccount;

	class Memento
	{
		int balance;
	public:
		explicit Memento(int balance) : balance(balance) {}

		friend class BankAccount;
	};

	class BankAccount
	{
		int balance{};
	public:
		explicit BankAccount(int balance)
			: balance(balance)
		{
		}

		Memento deposit(int amount)
		{
			balance += amount;
			return Memento{ balance };
		}

		void restore(const Memento & m)
		{
			balance = m.balance;
		}

		friend ostream & operator<<(ostream & out, BankAccount & ba)
		{
			return out << "balance: " << ba.balance << endl;
		}
	};
}
