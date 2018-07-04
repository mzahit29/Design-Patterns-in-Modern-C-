#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <ostream>

using namespace std;

class chat_room;

class person
{
	vector<string> chat_log_;
public:
	string name_;
	chat_room * chat_room_{ nullptr };
	explicit person(const string& name)
		: name_(name)
	{
	}
	~person() { cout << "~person()" << endl; }

	void say(const string & msg) const;
	void pm(const string & who, const string & msg) const;
	void receive(const string & origin, const string & msg);


	friend std::ostream& operator<<(std::ostream& os, const person& obj);
};