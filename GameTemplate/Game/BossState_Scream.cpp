#include "stdafx.h"
#include "BossState_Scream.h"
#include "Enemy_Boss.h"

void BossState_Scream::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Scream, 0.2f
	);
	if (m_enemy_Boss->GetIsPlayingAnimation() == false)
	{
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Scream::Update()
{
//	m_enemy_Boss->SetisUnderPattern(false);
}
