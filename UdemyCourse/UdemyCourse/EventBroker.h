#pragma once
#include "stdafx.h"
#include <string>
#include <boost/signals2/signal.hpp>

using namespace boost::signals2;
using namespace std;

class EventData
{
public:
	virtual void print() const = 0;
};


class PlayerScoredEvent : public EventData
{
	string name_;
	int goals_scored_;
public:
	explicit PlayerScoredEvent(const string& name, int goals_scored)
		: name_(name), goals_scored_(goals_scored)
	{
	}

	void print() const override
	{
		cout << name_ << " has scored! (their " << goals_scored_ << " goal)" << endl;
	}
};

namespace Mediator
{
	class Game
	{
	public:
		signal<void(EventData*)> events;
	};
}


class Player
{
	string name_;
	int goals_scored{};
	Mediator::Game & game;
public:

	Player(const string& name, Mediator::Game& game)
		: name_(name),
		  game(game)
	{
	}

	void score()
	{
		goals_scored++;
		PlayerScoredEvent ps{ name_, goals_scored };
		game.events(&ps);

	}
};

class Coach
{
	Mediator::Game & game_;
public:

	explicit Coach(Mediator::Game& game)
		: game_(game)
	{
		game_.events.connect([](EventData *e)
		{
			PlayerScoredEvent *ps = dynamic_cast<PlayerScoredEvent*>(e);
			if (ps)
			{
				ps->print();
			}
		});
	}
};
