#include "stdafx.h"
#include "OwnedState.h"
#include "ClosedState.h"
#include "Item.h"
#include "Modifier.h"
#include "ScaleYModifier.h"
#include "MoveYModifier.h"
#include "Scene.h"
#include "OpeningState.h"
#include "TimerHandler.h"
extern Scene* scene;
extern int points;
extern bool isEnd;


OwnedState::OwnedState(shared_ptr<Chain> chain)
	: State(chain){
}

OwnedState::OwnedState()
	: State(NULL){
}

void OwnedState::onInit(){
	if ( !isEnd )
		points++;

	m_item->m_block->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.38f, 0.0f, -3.8f, m_item->m_block, [](void* context)->void {
		State* outer = (State*)context;
		outer->m_item->m_block->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.2f, -3.8f, -3.5f, outer->m_item->m_block, [](void* context)->void {
			State* outer = (State*)context;
			outer->m_item->m_block->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.25f, -3.5f, -4.4f, outer->m_item->m_block, [](void* context)->void {
				State* outer = (State*)context;

				outer->m_item->m_block->m_pos_offset.y = 0.0f;
			}, outer)));
		}, outer)));

		outer->m_item->registerModifier(shared_ptr<Modifier>(new ScaleYModifier(0.2f, 1.0f, 0.7f, outer->m_item, [](void* context)->void{
			scene->registerUpdateHandler(shared_ptr<TimerHandler>(new TimerHandler(1.0f, false, [](void* context)->void{
				State* outer = (State*)context;

				outer->m_item->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.1f, 0.0f, -1.3f, outer->m_item, [](void* context)->void{
					State* outer = (State*)context;

					if (outer->m_nextState != NULL)
						outer->m_item->changeState(outer->m_nextState);
					else {
						if (outer->m_chain != NULL)
							outer->m_item->changeState(shared_ptr<State>(new ClosedState(outer->m_chain)));
						else
							outer->m_item->changeState(shared_ptr<State>(new ClosedState()));
					}
				}, context)));
			}, context)));
		}, outer)));
	}, this)));
}

void OwnedState::changeStateOnEnd(shared_ptr<State> state){
	m_nextState = state;
}

void OwnedState::enqueueOpening(int hole_num){
	scene->items[hole_num]->getState()->changeStateOnEnd(shared_ptr<State>(new ClosedState(shared_ptr<Chain>(new Chain(0.5f, hole_num, true)))));
}