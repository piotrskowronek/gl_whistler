#pragma once
#include "stdafx.h"
#include "State.h"
#include "Chain.h"
#include "TimerHandler.h"

class OpenedState : public State
{
private:
	shared_ptr<TimerHandler> m_update_handler;
public:
	OpenedState(shared_ptr<Chain>);
	OpenedState();
	void terminate();
	void onInit();
	void onKeyDown(unsigned char key, int x, int y);
	void enqueueOpening(int);
};