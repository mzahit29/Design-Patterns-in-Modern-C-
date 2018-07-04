#pragma once
#include "stdafx.h"
#include <iostream>
#include <ostream>
using namespace std;

namespace MementoNS
{
	class BankAccount;

	class Memento
	{
		int balance;
	public:
		explicit Memento(int balance) : balance(balance) {}

		friend class BankAccount;
		friend class BankAccount2;
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


	// BankAccount which keeps the vector of Mementos
	class BankAccount2
	{
		vector<std::shared_ptr<Memento>> changes;
		size_t current{};

		int balance{};
	public:
		explicit BankAccount2(int balance) : balance(balance)
		{
			// Store the initial state of bank account on slot 0
			current = 0;
			changes.push_back(std::make_shared<Memento>(balance));
		}

		std::shared_ptr<Memento> deposit(int amount)
		{
			balance += amount;
			auto m = std::make_shared<Memento>(balance);
			changes.push_back(m);
			++current;
			return m;
		}

		void restore(std::shared_ptr<Memento> & m)
		{
			if (m)
			{
				balance = m->balance;
				changes.push_back(std::make_shared<Memento>(balance));
				current = changes.size() - 1;
			}
		}

		std::shared_ptr<Memento> undo()
		{
			if (current > 0) {
				--current;
				std::shared_ptr<Memento> m = changes[current];
				balance = m->balance;
				return m;
			}

			return std::shared_ptr<Memento>{};
		}

		std::shared_ptr<Memento> redo()
		{
			if (current + 1 < changes.size())
			{
				++current;
				auto m = changes[current];
				balance = m->balance;
				return m;
			}

			return std::shared_ptr<Memento>{};
		}


		friend std::ostream& operator<<(std::ostream& os, const BankAccount2& obj)
		{
			return os
				<< "current: " << obj.current
				<< " balance: " << obj.balance << endl;
		}
	};
}
