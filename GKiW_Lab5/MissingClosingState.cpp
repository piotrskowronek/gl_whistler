#include "stdafx.h"
#include "MissingClosingState.h"
#include "ClosedState.h"
#include "Item.h"
#include "Modifier.h"
#include "MoveYModifier.h"
#include "Scene.h"
#include "OpeningState.h"
#include "Light.h"
#include "LightModifier.h"
extern Scene* scene;
extern int lives;
extern Light* light;
extern bool isEnd;


MissingClosingState::MissingClosingState(shared_ptr<Chain> chain)
	: State(chain){
}

MissingClosingState::MissingClosingState()
	: State(NULL){
}

void MissingClosingState::onInit(){
	if ( lives > 0 )
		lives--;

	if ( lives <= 0 && !isEnd ){
		isEnd = true;

		light->registerModifier(shared_ptr<Modifier>(new LightModifier(3.0f, 1.0f, 0.0f, light, [](void* context)->void{
			glutLeaveMainLoop();
		}, NULL)));
	}

	m_item->registerModifier(shared_ptr<Modifier>(new MoveYModifier(0.2f, 0.0f, -1.3f, m_item, [](void* context)->void{
		State* outer = (State*)context;

		if (outer->m_nextState != NULL)
			outer->m_item->changeState(outer->m_nextState);
		else {
			if (outer->m_chain != NULL)
				outer->m_item->changeState(shared_ptr<State>(new ClosedState(outer->m_chain)));
			else
				outer->m_item->changeState(shared_ptr<State>(new ClosedState()));
		}
	}, this)));
}

void MissingClosingState::changeStateOnEnd(shared_ptr<State> state){
	m_nextState = state;
}

void MissingClosingState::enqueueOpening(int hole_num){
	scene->items[hole_num]->getState()->changeStateOnEnd(shared_ptr<State>(new ClosedState(shared_ptr<Chain>(new Chain(0.5f, hole_num, true)))));
}