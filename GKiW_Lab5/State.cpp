#include "stdafx.h"
#include "State.h"


State::State(shared_ptr<Chain> chain)
	: m_chain(chain){
}

void State::initialize(Item* item){
	m_item = item;
}

void State::changeStateOnEnd(shared_ptr<State> state)
{
	m_nextState = state;
}
