#include "stdafx.h"
#include "BossState_FlyShoot.h"
#include "Enemy_Boss.h"

void BossState_FlyShoot::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_FlyShoot, 0.2f
	);
	if (m_enemy_Boss->GetisFlyShoot()&& m_enemy_Boss->GetIsPlayingAnimation() == false)
	{
		m_enemy_Boss->SetisLanding(true);
	}
}

void BossState_FlyShoot::Update()
{
	if (m_enemy_Boss->GetisLanding()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
	}
	m_enemy_Boss->SetisFlyShoot(false);
}
