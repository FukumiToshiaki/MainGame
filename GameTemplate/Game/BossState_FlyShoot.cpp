#include "stdafx.h"
#include "BossState_FlyShoot.h"
#include "Enemy_Boss.h"

void BossState_FlyShoot::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_FlyShoot_Animation, 0.2f
	);
	if (m_enemy_Boss->GetIsPlayingAnimation() == false)
	{
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
	}
}

void BossState_FlyShoot::Update()
{
	//m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	//m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
}
