#include "stdafx.h"
#include "Personnn.h"
#include "ChatRoom.h"
#include <sstream>

void person::say(const string & msg) const
{
	chat_room_->broadcast(name_, msg);
}

void person::pm(const string & who ,const string & msg) const
{
	chat_room_->pm(name_, who, msg);
}

void person::receive(const string & origin, const string & msg)
{
	ostringstream oss;
	oss << origin << ": " << msg;
	chat_log_.push_back(oss.str());
}

std::ostream& operator<<(std::ostream& os, const person& obj)
{
	os << "name_: " << obj.name_ << endl;
	for (auto & x : obj.chat_log_)
	{
		os << x << endl;
	}
	return os;
}