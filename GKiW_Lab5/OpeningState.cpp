#include "stdafx.h"
#include "OpeningState.h"
#include "OpenedState.h"
#include "Item.h"
#include "Modifier.h"
#include "MoveYModifier.h"


OpeningState::OpeningState(shared_ptr<Chain> chain)
	: State(chain){
}

void OpeningState::onInit(){
	m_item->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.3f, -1.3f, -0.3f, m_item, [](void* context)->void{
		OpeningState* outer = (OpeningState*)context;

		if (outer->m_nextState != NULL)
			outer->m_item->changeState(outer->m_nextState);
		else {
			if (outer->m_chain != NULL)
				outer->m_item->changeState(shared_ptr<State>(new OpenedState(outer->m_chain)));
			else
				outer->m_item->changeState(shared_ptr<State>(new OpenedState()));
		}
	}, this)));
}

void OpeningState::changeStateOnEnd(shared_ptr<State> state){
	m_nextState = state;
}