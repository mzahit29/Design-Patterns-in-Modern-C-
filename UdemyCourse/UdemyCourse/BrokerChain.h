#pragma once
#include <boost/signals2.hpp>
#include <string>

using namespace std;

namespace BrokerChain
{
	// A structure for finding out the following information
	// My name is "red_goblin", my current attack is 4, what should my attack be after modification? Store it in result_
	struct Query
	{
		string creature_name_;
		enum Argument {attack, life} argument_;
		int result_;

	public:
		Query(const string& creature_name, Argument argument, int result)
			: creature_name_(creature_name),
			  argument_(argument),
			  result_(result)
		{
		}
	};
	struct Game  // Mediator
	{
		boost::signals2::signal<void(Query&)> queries_;
	};

	struct Creature
	{
		Game& game_;
		int attack_, life_;
		string name_;
	public:

		Creature(Game& game, int attack, int life, const string& name)
			: game_(game),
			  attack_(attack),
			  life_(life),
			  name_(name)
		{
		}

		int get_attack() const
		{
			// Ask what your attack should be, queries_ contains functions void(Query &) that modify
			// the query references
			Query q{ name_, Query::Argument::attack, attack_ };
			// The query reference is passed to all the queries inside game.queries_, therefore the effect is cumulative
			game_.queries_(q);
			return q.result_;
		}

		int get_life() const
		{
			Query q{ name_, Query::Argument::life, life_ };
			game_.queries_(q);
			return q.result_;
		}

		friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
		{
			return os
				<< "attack_: " << obj.get_attack()
				<< " life_: " << obj.get_life()
				<< " name_: " << obj.name_;
		}
	};

	class CreatureModifier
	{
		Game& game_;
		Creature& creature_;
	public:

		CreatureModifier(Game& game, Creature& creature)
			: game_(game),
			  creature_(creature)
		{
		}
		virtual ~CreatureModifier() = default;
	};

	class DoubleAttackModifier : public CreatureModifier
	{
		boost::signals2::connection conn;
	public:

		DoubleAttackModifier(Game& game, Creature& creature) // Give this creature, in this game a double attack ability
			: CreatureModifier(game, creature)
		{
			// Here we are passing a function to the queries_ which will double the result only if the asked query is for
			// that specific creatre and argument is of type attack. What this means is lets say you create a 
			// DoubleAttackModifier for a specific game and say a creature named red_goblin. This lambda function takes
			// a query by reference and in that query you specify the name of the creature, attack or life, and current value of 
			// that attribute. It checks the name of the creature if it is "red_goblin" and queried attribute is attack then
			// it doubles the provided value.
			conn = game.queries_.connect([&](Query& q)
			{
				if (q.creature_name_ == creature.name_ &&
					q.argument_ == Query::Argument::attack)
				{
					cout << "Double attack modifier query" << endl;
					q.result_ *= 2;
				}
			});
		}

		~DoubleAttackModifier()
		{
			conn.disconnect();
		}
	};

	// I want the following creature modifier to affect all creatures. However creature modifier requires a specific creature
	// reference. But I want this modifier to affect all creatures.
	class AllCreaturesDie
	{
		Game& game_;
		signals2::connection conn_;
	public:


		AllCreaturesDie(Game& game) : game_(game)
		{
			conn_ = game_.queries_.connect([](BrokerChain::Query& q)
			{
				cout << "All creatures die modifier query" << endl;
				if (q.argument_ == Query::Argument::life)	q.result_ = 0;
			});
		}
		~AllCreaturesDie()
		{
			conn_.disconnect();
		}
	};

	class AllCreaturesLifeBonusPlus10
	{
		Game& game_;
		signals2::connection conn_;
	public:


		AllCreaturesLifeBonusPlus10(Game& game) : game_(game)
		{
			conn_ = game_.queries_.connect([](BrokerChain::Query& q)
			{
				cout << "All creatures life plus 10 modifier query" << endl;
				if (q.argument_ == Query::Argument::life)	q.result_ += 10;
			});
		}
		~AllCreaturesLifeBonusPlus10()
		{
			conn_.disconnect();
		}
	};
}
