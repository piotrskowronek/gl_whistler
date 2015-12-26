#include "stdafx.h"
#include "OpenedState.h"
#include "Item.h"


void OpenedState::onInit(){
	/*if ( chain != null )
	{
		chain.onClosedState();
	}*/
		
	m_item->m_pos_offset.y = 0.0f;
}