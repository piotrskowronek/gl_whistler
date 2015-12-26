#include "stdafx.h"
#include "OpeningState.h"
#include "Item.h"


void OpeningState::onInit(){
	/*if ( chain != null )
	{
		chain.onClosedState();
	}*/
		
	m_item->m_pos_offset.y = 0.0f;
}