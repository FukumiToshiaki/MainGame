#pragma once
#include "IBossState.h"
#include "Enemy_Boss.h"

class BossState_Fly : public IBossState
{
public:
	BossState_Fly(Enemy_Boss* enemy_Boss, Enemy_Boss::EnState nextState) :
		IBossState(enemy_Boss), m_enNextState(nextState) {};

	void Animation() override;

	void Update() override;

private:
	Enemy_Boss::EnState m_enNextState; // takeoff終了時に遷移する状態
	float m_flyTime = 5.0f;
};
