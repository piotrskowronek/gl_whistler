#pragma once
#include "stdafx.h"
#include "vector"

class Level {
protected:
	float duration;
	float opened_duration;
	vector<string> sequences_code;
public:
	void start();
};