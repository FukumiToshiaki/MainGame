#pragma once
#include "IBossState.h"
class BossState_FlyAttack : public IBossState
{
public:
	BossState_FlyAttack(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:

};

