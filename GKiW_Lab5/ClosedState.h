#pragma once
#include "stdafx.h"
#include "State.h"
#include "Chain.h"

class ClosedState : public State
{
public:
	ClosedState(shared_ptr<Chain>);
	ClosedState();
	void onInit();
};