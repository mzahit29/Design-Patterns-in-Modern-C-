#pragma once
#include <array>
#include <numeric>

class Creature
{
	enum Abilities {str, agl, intel, count};
	std::array<int, count> abilities;
public:
	void set_strength(int x) { abilities[str] = x; }
	int get_strength() { return abilities[str]; }
	void set_agility(int x) { abilities[agl] = x; }
	int get_agility() { return abilities[agl]; }
	void set_intel(int x) { abilities[intel] = x; }
	int get_intel() { return abilities[intel]; }

	int sum()
	{
		return std::accumulate(abilities.begin(), abilities.end(), 0);
	}
	float avg()
	{
		return sum() / (double)count;
	}
	int max()
	{
		return *std::max_element(abilities.begin(), abilities.end());
	}
};
