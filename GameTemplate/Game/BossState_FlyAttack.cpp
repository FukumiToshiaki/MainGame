#include "stdafx.h"
#include "BossState_FlyAttack.h"
#include "Enemy_Boss.h"

void BossState_FlyAttack::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Fly, 0.2f
	);
	if (m_flyTime <= 0) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
		m_flyTime = rand() % 3;
		m_enemy_Boss->SetisUnderFlyAttack(false);
	}
}

void BossState_FlyAttack::Update()
{
	m_flyTime -= g_gameTime->GetFrameDeltaTime();

	//m_enemy_Boss->SetUnderFlyAttack(false);
}
