#include "stdafx.h"
#include "ClosedState.h"
#include "Item.h"
#include "Scene.h"
#include "OpeningState.h"
extern Scene* scene;


ClosedState::ClosedState(shared_ptr<Chain> chain)
	: State(chain){
}

ClosedState::ClosedState()
	: State(NULL){
}

void ClosedState::onInit(){
	if ( m_chain != NULL )
	{
		m_chain->onClosedState();
	}
		
	m_item->m_pos_offset.y = -1.3f;
}

void ClosedState::enqueueOpening(int hole_num){
	scene->items[hole_num]->changeState(shared_ptr<State>(new OpeningState(shared_ptr<Chain>(new Chain(0.5f, hole_num, false)))));
}