#include "stdafx.h"
#include "OpenedState.h"
#include "MissingClosingState.h"
#include "Item.h"
#include "TimerHandler.h"
#include "Scene.h"
#include "OpeningState.h"
#include "OwnedState.h"
extern Scene* scene;


OpenedState::OpenedState(shared_ptr<Chain> chain)
	: State(chain){
}

OpenedState::OpenedState()
	: State(NULL){
}

void OpenedState::onInit(){
	m_item->m_pos_offset.y = 0.0f;
	m_item->m_scale_multipler.y = 1.0f;

	m_update_handler = shared_ptr<TimerHandler>(new TimerHandler(1.0f, false, [](void* context)->void{
		State* outer = (State*)context;
		outer->m_item->getState()->terminate();
	}, this));
	scene->registerUpdateHandler(m_update_handler);
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

void OpenedState::onKeyDown(unsigned char key, int x, int y){
	if ( m_item->m_key != key )
		return;

	scene->unregisterUpdateHandler(m_update_handler);

	if (m_chain != NULL)
		m_item->changeState(shared_ptr<State>(new OwnedState(m_chain)));
	else
		m_item->changeState(shared_ptr<State>(new OwnedState()));
}