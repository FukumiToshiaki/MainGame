#include "stdafx.h"
#include "BossState_Landing.h"
#include "Enemy_Boss.h"

void BossState_Landing::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Landing, 0.2f
	);
	if (m_enemy_Boss->GetIsPlayingAnimation() == false && m_enemy_Boss->GetisLanding())
	{
		m_enemy_Boss->SetisLanding(false);
		m_enemy_Boss->SetisIdle(true);
	}
}

void BossState_Landing::Update()
{
	if (m_enemy_Boss->GetisIdle() && !m_enemy_Boss->GetisLanding()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
//	m_enemy_Boss->SetisUnderPattern(false);
}
