#include "stdafx.h"
#include "MissingClosingState.h"
#include "ClosedState.h"
#include "Item.h"
#include "Modifier.h"
#include "MoveYModifier.h"
#include "Scene.h"
#include "OpeningState.h"s
extern Scene* scene;


MissingClosingState::MissingClosingState(shared_ptr<Chain> chain)
	: State(chain){
}

MissingClosingState::MissingClosingState()
	: State(NULL){
}

void MissingClosingState::onInit(){
	m_item->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.2f, 0.0f, -1.3f, m_item, [](void* context)->void{
		State* outer = (State*)context;

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

void MissingClosingState::enqueueOpening(int hole_num){
	scene->items[hole_num]->getState()->changeStateOnEnd(shared_ptr<State>(new ClosedState(shared_ptr<Chain>(new Chain(0.5f, hole_num, true)))));
}