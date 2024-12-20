#pragma once
#include "IBossState.h"
class BossState_Rest : public IBossState
{
public:
	BossState_Rest(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;


private:

};

