#pragma once
#include "IBossState.h"
class BossState_Takeoff : public IBossState
{
public:
	BossState_Takeoff(Enemy_Boss* enemy_Boss, int nextState) :
		IBossState(enemy_Boss), m_enNextState(nextState){};

	void Animation() override;

	void Update() override;

private:
	int m_enNextState; // takeoffI—¹‚É‘JˆÚ‚·‚éó‘Ô
};

