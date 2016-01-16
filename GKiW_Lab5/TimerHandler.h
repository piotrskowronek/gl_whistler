#pragma once
#include "stdafx.h"
#include <memory>
#include <time.h>
#define TH_CALLBACK void (*p)(void*)


class TimerHandler {
protected:
	bool m_repeat;
	clock_t m_birth;
	TH_CALLBACK;
public:
	void* m_context;
	float m_duration;

	TimerHandler(float duration, bool repeat, TH_CALLBACK, void* context);
	~TimerHandler();
	void windUpClock();
	void onUpdate();
	bool isTerminated();
	bool TimerHandler::operator ==(const TimerHandler& other);
private:
	bool isReadyToTick();
};