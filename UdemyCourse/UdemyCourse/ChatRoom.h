#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;

class chat_room
{
	vector<person *> people_;
public:
	void enter(person & p);

	void broadcast(const string & origin, const string & msg);
	void pm(const string & origin, const string & receiver, const string & msg);
};