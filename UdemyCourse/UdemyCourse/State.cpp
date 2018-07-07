#include "stdafx.h"
#include "State.h"

void OnState::off(LightSwitch *ls)
{
	ls->state_ = new OffState();
	// ls->state was pointing to "this", so now we can delete it
	delete this;
}

void OffState::on(LightSwitch* ls)
{
	ls->state_ = new OnState();
	// ls->state was pointing to "this", so now we can delete it
	delete this;
}
