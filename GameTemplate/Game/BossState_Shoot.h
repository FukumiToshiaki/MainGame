#pragma once
#include "IBossState.h"
class BossState_Shoot : public IBossState
{
public:
	BossState_Shoot(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:

};

