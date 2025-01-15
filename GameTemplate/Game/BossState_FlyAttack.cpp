#include "stdafx.h"
#include "BossState_FlyAttack.h"
#include "Enemy_Boss.h"

void BossState_FlyAttack::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Fly, 0.2f
	);
	if (m_enemy_Boss->GetIsPlayingAnimation() == false ) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
	}
}

void BossState_FlyAttack::Update()
{
	//m_enemy_Boss->SetUnderFlyAttack(false);
}
