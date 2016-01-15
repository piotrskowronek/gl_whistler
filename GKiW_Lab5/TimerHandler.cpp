#include "stdafx.h"
#include "TimerHandler.h"
#include <time.h>


TimerHandler::TimerHandler(float duration, bool repeat, TH_CALLBACK, void* context)
	: m_duration(duration)
	, m_repeat(repeat)
	, m_context(context)
	, m_birth(clock())
{
	this->p = p;
}

TimerHandler::~TimerHandler(){
	//delete m_context;
}

void TimerHandler::windUpClock(){
	m_birth = clock();
}

void TimerHandler::onUpdate(){
	if ( isReadyToTick() )
		p(m_context);
}

bool TimerHandler::isTerminated(){
	bool ready = isReadyToTick();
	if ( ready )
		m_birth = clock();

	if (m_repeat)
		return false;

	return ready;
}

bool TimerHandler::isReadyToTick(){
	clock_t end = clock();
	double elapsed_secs = double(end - m_birth) / CLOCKS_PER_SEC;
	
	if ( elapsed_secs >= m_duration )
		return true;
	return false;
}

bool TimerHandler::operator ==(const TimerHandler& other) {
    return (
		m_duration == other.m_duration &&
		m_repeat == other.m_repeat &&
		m_context == other.m_context &&
		m_birth == other.m_birth
	);
}