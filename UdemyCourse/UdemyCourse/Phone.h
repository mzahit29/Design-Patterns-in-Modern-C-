#pragma once
#include"stdafx.h"
#include <ostream>
#include <map>
#include <vector>

using namespace std;

enum class PhoneState
{
	off_hook,
	connecting,
	connected,
	on_hold,
	on_hook
};


inline ostream & operator<<(ostream & out, const PhoneState & phone_state)
{
	switch(phone_state)
	{
	case PhoneState::off_hook:
		out << "Off the hook";
		break;
	case PhoneState::connecting:
		out << "Connecting";
		break;
	case PhoneState::connected:
		out << "Connected";
		break;
	case PhoneState::on_hold:
		out << "On hold";
		break;
	case PhoneState::on_hook:
		out << "On hook";
		break;
	default:
		out << "ERROR: Wrong phone state";
		break;
	}

	return out;
}



enum class Trigger
{
	call_dialed,
	hung_up,
	call_connected,
	placed_on_hold,
	taken_off_hold,
	left_message,
	stop_using_phone
};


inline ostream & operator<<(ostream & out, const Trigger & t)
{
	switch(t)
	{
	case Trigger::call_dialed:
		out << "Call dialed";
		break;
	case Trigger::hung_up:
		out << "Hung up";
		break;
	case Trigger::call_connected:
		out << "Call connected";
		break;
	case Trigger::placed_on_hold:
		out << "Placed on hold";
		break;
	case Trigger::taken_off_hold:
		out << "Taken off hold";
		break;
	case Trigger::left_message:
		out << "Left message";
		break;
	case Trigger::stop_using_phone:
		out << "Stop using phone";
		break;
	default:
		out << "ERROR: Wrong Trigger state";
		break;
	}

	return out;
}