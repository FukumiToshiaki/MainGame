#pragma once
#include "IBossState.h"
class BossState_Fly : public IBossState
{
public:
	BossState_Fly(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:

};
