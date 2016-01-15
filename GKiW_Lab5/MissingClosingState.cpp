#include "stdafx.h"
#include "MissingClosingState.h"
#include "ClosedState.h"
#include "Item.h"
#include "Modifier.h"
#include "MoveYModifier.h"


MissingClosingState::MissingClosingState(shared_ptr<Chain> chain)
	: State(chain){
}

MissingClosingState::MissingClosingState()
	: State(NULL){
}

void MissingClosingState::onInit(){
	m_item->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.3f, -0.3f, -1.3f, m_item, [](void* context)->void{
		MissingClosingState* outer = (MissingClosingState*)context;

		if (outer->m_nextState != NULL)
			outer->m_item->changeState(outer->m_nextState);
		else {
			if (outer->m_chain != NULL)
				outer->m_item->changeState(shared_ptr<State>(new ClosedState(outer->m_chain)));
			else
				outer->m_item->changeState(shared_ptr<State>(new ClosedState()));
		}
	}, this)));
}

void MissingClosingState::changeStateOnEnd(shared_ptr<State> state){
	m_nextState = state;
}