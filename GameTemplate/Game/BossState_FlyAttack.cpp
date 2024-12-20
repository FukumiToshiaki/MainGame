#include "stdafx.h"
#include "BossState_FlyAttack.h"
#include "Enemy_Boss.h"

void BossState_FlyAttack::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Fly, 0.2f
	);
}

void BossState_FlyAttack::Update()
{
	if (m_enemy_Boss->GetisLanding()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
	}
	m_enemy_Boss->SetisFlyAttack(false);
}
