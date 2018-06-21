#pragma once
#include <ostream>

namespace ChainOfResp
{
	class Creature
	{
	public:
		int attack_, defense_, life_;
		Creature(int attack, int defense, int life)
			: attack_(attack),
			defense_(defense),
			life_(life)
		{
		}


		friend std::ostream& operator<<(std::ostream& os, const Creature& obj)
		{
			return os
				<< "attack_: " << obj.attack_
				<< " defense_: " << obj.defense_
				<< " life_: " << obj.life_;
		}
	};

	class CreatureModifier
	{
		CreatureModifier *next_modifier_{ nullptr };
	protected:
		Creature & creature_;
	public:
		explicit CreatureModifier(Creature& creature)
			: creature_(creature)
		{
		}

		void add_modifier(CreatureModifier *modifier)
		{
			// We have a linked list of creature modifiers
			if (next_modifier_) next_modifier_->add_modifier(modifier);
			else next_modifier_ = modifier;
		}

		void add_modifier_beg(CreatureModifier *modifier)
		{
			if (next_modifier_)
			{
				modifier->next_modifier_ = next_modifier_;
			}

			next_modifier_ = modifier;
		}

		// Base modifier only calls the next virtual handle() on the chain, this is called by the overriden handle() 
		// methods
		virtual void handle()
		{
			if (next_modifier_) next_modifier_->handle();
		}


	};

	class DoubleAttackModifier : public CreatureModifier
	{
	public:

		explicit DoubleAttackModifier(Creature& creature)
			: CreatureModifier(creature)
		{
		}

		virtual void handle() override
		{
			// Do this modifier's work and propagate down the chain
			creature_.attack_ *= 2;
			CreatureModifier::handle();
		}
	};

	class RageModifier : public CreatureModifier
	{
	public:

		explicit RageModifier(Creature& creature)
			: CreatureModifier(creature)
		{
		}

		void handle() override
		{
			creature_.life_ *= 1.4f;
		}
	};

	class NegateSpells : public CreatureModifier
	{
	public:
		explicit NegateSpells(Creature& creature)
			: CreatureModifier(creature)
		{
		}

		void handle() override
		{
			// Do nothing, do not call the base handle() which propagates the handle to the chain
			// Therefore it will stop the spell effects.
		}
	};
}
