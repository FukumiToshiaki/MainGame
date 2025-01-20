#pragma once
#include "IBossState.h"
class BossState_Defence : public IBossState
{
public:
	BossState_Defence(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:
	float m_defenceTime = 4.0f;
};

