#pragma once
#include "IBossState.h"
class BossState_Walk :public IBossState
{
public:
	BossState_Walk(Enemy_Boss* enemy_Boss):
	IBossState(enemy_Boss) {};

	void Animation() override;

	void Update() override;

};

