#pragma once
#include "stdafx.h"
#include "State.h"
#include "Chain.h"


class MissingClosingState : public State
{
public:
	//outer
	shared_ptr<State> m_nextState;
	shared_ptr<Chain> m_chain;

	MissingClosingState(shared_ptr<Chain>);
	MissingClosingState();
	void changeStateOnEnd(shared_ptr<State> state);
	void onInit();
	void enqueueOpening(int);
};