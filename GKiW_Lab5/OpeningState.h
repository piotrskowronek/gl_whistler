#pragma once
#include "stdafx.h"
#include "State.h"
#include "Chain.h"


class OpeningState : public State
{
public:
	//outer
	shared_ptr<State> m_nextState;
	shared_ptr<Chain> m_chain;

	OpeningState(shared_ptr<Chain>);
	void changeStateOnEnd(shared_ptr<State> state);
	void onInit();
	void enqueueOpening(int);
};