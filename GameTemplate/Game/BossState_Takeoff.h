#pragma once
#include "IBossState.h"
class BossState_Takeoff : public IBossState
{
public:
	BossState_Takeoff(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:

};

