#pragma once
#include "stdafx.h"
#include "Chain.h"

class Item;

class State
{
public:
	//outer
	Item* m_item;
	shared_ptr<Chain> m_chain;
	shared_ptr<State> m_nextState;

	State(shared_ptr<Chain>);
	void initialize(Item*);
	void changeStateOnEnd(shared_ptr<State>);
	virtual void terminate() {};
	virtual void onInit() {};
};