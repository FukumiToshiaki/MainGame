#pragma once
#include "IBossState.h"
class BossState_Scream : public IBossState
{
public:
	BossState_Scream(Enemy_Boss* enemy_Boss) :
		IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

private:

};

