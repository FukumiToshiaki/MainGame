#include "stdafx.h"
#include "BossState_FlyShoot.h"
#include "Enemy_Boss.h"

void BossState_FlyShoot::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_FlyShoot_Animation, 0.2f
	);
	//アニメーションが終わったら次のアニメーション
	if (m_enemy_Boss->GetIsPlayingAnimation() == false)
	{
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
	}
}

void BossState_FlyShoot::Update()
{
}
