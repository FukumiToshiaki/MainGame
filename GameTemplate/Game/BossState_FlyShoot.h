#pragma once
#include "IBossState.h"
class BossState_FlyShoot : public IBossState
{
public:
	BossState_FlyShoot(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:

};

