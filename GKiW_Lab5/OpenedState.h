#pragma once
#include "stdafx.h"
#include "State.h"
#include "Chain.h"

class OpenedState : public State
{
public:
	OpenedState(shared_ptr<Chain>);
	OpenedState();
	void terminate();
	void onInit();
	void enqueueOpening(int);
};