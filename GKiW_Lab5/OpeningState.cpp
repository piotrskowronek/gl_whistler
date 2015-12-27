#include "stdafx.h"
#include "OpeningState.h"
#include "Item.h"
#include "Modifier.h"
#include "MoveYModifier.h"


void OpeningState::onInit(){
	/*if ( chain != null )
	{
		chain.onClosedState();
	}*/
		
	m_item->m_pos_offset.y = -1.3f;
	m_item->registerModifier(shared_ptr<Modifier>(new MoveYModifier(1.0f, -1.3f, 0.0f)));
}