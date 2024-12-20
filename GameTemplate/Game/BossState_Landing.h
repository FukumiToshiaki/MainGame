#pragma once
#include "IBossState.h"
class BossState_Landing : public IBossState
{
public:
	BossState_Landing(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:
};

