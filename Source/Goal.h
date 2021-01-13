#pragma once
#include "GameObject.h"

class Goal
	: public GameObject
{
public:
	Goal(float _x);
	void Update();
	void setCompleted(bool _param);
	bool wasCompleted();

private:
	bool m_isCompleted, m_wasCompleted;
};

