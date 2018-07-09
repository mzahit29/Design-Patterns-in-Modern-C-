#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;

class Game
{
public:
	explicit Game(int num_of_players)
		: num_of_players(num_of_players)
	{
	}

	// General skeleton of the algorithm
	void run()
	{
		start();
		while (!have_winner())
		{
			take_turn();
		}
		cout << "Player " << get_winner() << " wins." << endl;
	}
protected:
	int num_of_players;
	int current_player{ 0 };
	virtual void start() = 0;
	virtual bool have_winner() = 0;
	virtual void take_turn() = 0;
	virtual int get_winner() = 0;
};


class Chess : public Game
{
	int turn{ 0 }, max_turn{ 10 };
public:
	explicit Chess()
		: Game(2)
	{
	}


protected:
	void start() override
	{
		cout << "Chess game started with " << num_of_players << " players." << endl;
	}
	bool have_winner() override
	{
		return turn == max_turn;
	}
	void take_turn() override
	{
		cout << "Turn " << turn << " taken by player " << current_player << endl;
		++turn;
		current_player = (current_player + 1) % num_of_players;
	}
	int get_winner() override
	{
		return current_player;
	}
};