#include "stdafx.h"
#include "OpenedState.h"
#include "MissingClosingState.h"
#include "Item.h"
#include "TimerHandler.h"
#include "Scene.h"
#include "OpeningState.h"
extern Scene* scene;


OpenedState::OpenedState(shared_ptr<Chain> chain)
	: State(chain){
}

OpenedState::OpenedState()
	: State(NULL){
}

void OpenedState::onInit(){
	m_item->m_pos_offset.y = 0.0f;

	scene->registerUpdateHandler(shared_ptr<TimerHandler>(new TimerHandler(0.5f, false, [](void* context)->void{
		State* outer = (State*)context;
		outer->m_item->getState()->terminate();
	}, this)));
}

void OpenedState::terminate(){
	if ( m_nextState != NULL )
		m_item->changeState( m_nextState );
	else {
		if ( m_chain != NULL )
			m_item->changeState(shared_ptr<State>(new MissingClosingState(m_chain)));
		else
			m_item->changeState(shared_ptr<State>(new MissingClosingState()));
	}
}

void OpenedState::enqueueOpening(int hole_num){
	scene->items[hole_num]->getState()->changeStateOnEnd(shared_ptr<State>(new MissingClosingState(shared_ptr<Chain>(new Chain(0.5f, hole_num, true)))));
}