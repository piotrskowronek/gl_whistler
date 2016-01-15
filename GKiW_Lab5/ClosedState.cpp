#include "stdafx.h"
#include "ClosedState.h"
#include "Item.h"


ClosedState::ClosedState(shared_ptr<Chain> chain)
	: State(chain){
}

ClosedState::ClosedState()
	: State(NULL){
}

void ClosedState::onInit(){
	if ( m_chain != NULL )
	{
		//m_chain.onClosedState();
	}
		
	m_item->m_pos_offset.y = -1.3f;
}