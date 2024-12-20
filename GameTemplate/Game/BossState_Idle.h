#pragma once
#include "IBossState.h"

class BossState_Idle:public IBossState
{
public:
	BossState_Idle(Enemy_Boss* enemy_Boss):
	IBossState(enemy_Boss){};

	void Animation() override;

	void Update() override;


private:

};

