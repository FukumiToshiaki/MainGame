#pragma once
#include "IBossState.h"

class BossState_Die : public IBossState
{
public:
	BossState_Die(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:
};

