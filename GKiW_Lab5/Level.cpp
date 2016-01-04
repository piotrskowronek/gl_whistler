#include "stdafx.h"
#include "Level.h"
#include "TimerHandler.h"

void callback2(void* context){
	printf("OK");
}

void Level::start(){
	//shared_ptr<TimerHandler> handler(new TimerHandler(duration, false, callback2));
}