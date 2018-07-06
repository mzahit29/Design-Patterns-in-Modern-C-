#pragma once
#include "stdafx.h"

// Observer interface, will receive the event and do something with it
template <typename T>
class Observer 
{
public:
	virtual void field_changed(T &, const string & field_name) = 0;
};
