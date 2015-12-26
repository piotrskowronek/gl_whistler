#include "stdafx.h"
#include "ClosedState.h"
#include "Item.h"

void ClosedState::onInit(){
	/*if ( chain != null )
	{
		chain.onClosedState();
	}*/
		
	m_item->m_pos_offset.y = -1.3f;
}