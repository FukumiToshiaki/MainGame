#include "stdafx.h"
#include "BossState_Scream.h"
#include "Enemy_Boss.h"

void BossState_Scream::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Scream_Animation, 0.2f
	);
}

void BossState_Scream::Update()
{
	//アニメーションが終わったら
	if (!m_enemy_Boss->GetIsPlayingAnimation())
	{
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Rest);
	}
}
