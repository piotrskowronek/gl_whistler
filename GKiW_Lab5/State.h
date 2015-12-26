#pragma once
#include "stdafx.h"

class Item;

class State
{
protected:
	Item* m_item;
public:
	void initialize(Item*);
	virtual void onInit() {};
};