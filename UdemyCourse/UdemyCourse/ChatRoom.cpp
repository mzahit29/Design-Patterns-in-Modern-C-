#include "stdafx.h"
#include "Personnn.h"
#include "ChatRoom.h"
#include <algorithm>

void chat_room::enter(person & p)
{
	people_.push_back(&p);
	p.chat_room_ = this;

	for (person * person : people_)
	{
		string msg = p.name_ + " joins the chat";
		person->receive("room", msg);
	}
}

void chat_room::broadcast(const string & origin, const string & msg)
{
	for (person * p : people_)
	{
		// Do not broadcast message back to the origin
		if (p->name_ != origin)
			p->receive(origin, msg);
	}
}

void chat_room::pm(const string & origin, const string & receiver, const string & msg)
{

	auto target = std::find_if(people_.begin(), people_.end(),
		[&](const person *p)
	{
		return p->name_ == receiver;
	}
		);
	if (target != people_.end())
	{
		(*target)->receive(origin, msg);
	}
}