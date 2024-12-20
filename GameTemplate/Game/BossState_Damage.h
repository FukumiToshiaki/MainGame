#pragma once
#include "IBossState.h"
class BossState_Damage : public IBossState
{
public:
	BossState_Damage(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:
};

