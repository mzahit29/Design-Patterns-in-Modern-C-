#pragma once
#include "stdafx.h"
#include <iostream>

using namespace std;

class LightSwitch;

struct State
{
	virtual ~State() { cout << "~State()" << endl;  };
	virtual void off(LightSwitch *ls) { cout << "State is already OFF" << endl; }
	virtual void on(LightSwitch *ls) { cout << "State is already ON" << endl;  }
};

struct OnState : State
{
	OnState()
	{
		cout << "Light is turned ON" << endl;
	}
	~OnState()
	{
		cout << "~OnState()" << endl;
	}

	virtual void off(LightSwitch *ls) override;
};

struct OffState : State
{
	OffState()
	{
		cout << "Light is turned OFF" << endl;
	}
	~OffState()
	{
		cout << "~OffState()" << endl;
	}


	virtual void on(LightSwitch *ls) override;
};

class LightSwitch
{
public:
	State * state_;
	explicit LightSwitch()
	{
		cout << "LightSwitch()" << endl;
		state_ = new OffState();
	}
	~LightSwitch()
	{
		cout << "~LightSwitch()" << endl;
		delete state_;
	}

	void on()
	{
		state_->on(this);
	}
	void off()
	{
		state_->off(this);
	}
};
