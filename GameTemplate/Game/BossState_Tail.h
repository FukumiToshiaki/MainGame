#pragma once
#include "IBossState.h"
class BossState_Tail : public IBossState
{
public:
	BossState_Tail(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:

};

