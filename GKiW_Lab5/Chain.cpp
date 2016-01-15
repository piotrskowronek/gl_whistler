#include "stdafx.h"
#include "Chain.h"
#include "Scene.h"
#include "State.h"
#include "OpeningState.h"
#include "Item.h"
extern Scene* scene;

Chain::Chain(float opened_duration, int hole_num, bool activated)
	: m_opened_duration(opened_duration)
	, m_hole_num(hole_num)
	, m_activated(activated){
}

void Chain::onClosedState(){
	if (! m_activated)
		return;

	scene->items[m_hole_num]->changeState(shared_ptr<State>(new OpeningState(shared_ptr<Chain>(new Chain(m_opened_duration, m_hole_num, false)))));
}