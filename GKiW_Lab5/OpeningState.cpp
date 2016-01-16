#include "stdafx.h"
#include "OpeningState.h"
#include "OpenedState.h"
#include "Item.h"
#include "Modifier.h"
#include "MoveYModifier.h"
#include "Scene.h"
extern Scene* scene;


OpeningState::OpeningState(shared_ptr<Chain> chain)
	: State(chain){
}

void OpeningState::onInit(){
	m_item->m_scale_multipler.y = 1.0f;

	m_item->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.2f, -1.3f, -0.3f, m_item, [](void* context)->void{
		State* outer = (State*)context;

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

void OpeningState::enqueueOpening(int hole_num){
	scene->items[hole_num]->getState()->changeStateOnEnd(shared_ptr<State>(new OpenedState(shared_ptr<Chain>(new Chain(0.5f, hole_num, true)))));
}