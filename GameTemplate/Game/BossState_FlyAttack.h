#pragma once
#include "IBossState.h"

class BossState_FlyAttack : public IBossState
{
public:
	BossState_FlyAttack(Enemy_Boss* enemy_Boss,int nextState) :
		IBossState(enemy_Boss),m_enNextState(nextState) {};

	void Animation() override;

	void Update() override;

private:
	int m_enNextState; // takeoffI—¹‚É‘JˆÚ‚·‚éó‘Ô
	float m_flyAttackTime = 2.0f;
};

