#pragma once
#include "stdafx.h"

class Chain
{
private:
	float m_opened_duration;
	int m_hole_num;
	bool m_activated;
public:
	Chain(float opened_duration, int hole_num, bool activated);
	void onClosedState();
};