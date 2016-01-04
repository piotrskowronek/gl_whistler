#pragma once
#include "stdafx.h"
#include <memory>
#include <time.h>
#define TH_CALLBACK void (*p)(void*)


class TimerHandler {
protected:
	float m_duration;
	bool m_repeat;
	void* m_context;
	clock_t m_birth;
	TH_CALLBACK;
public:
	TimerHandler(float duration, bool repeat, TH_CALLBACK, void* context);
	~TimerHandler();
	void windUpClock();
	void onUpdate();
	bool isTerminated();
private:
	bool isReadyToTick();
};