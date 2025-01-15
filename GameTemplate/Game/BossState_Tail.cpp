#include "stdafx.h"
#include "BossState_Tail.h"
#include "Enemy_Boss.h"

void BossState_Tail::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Tail, 0.2f
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Tail::Update()
{
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());

	//m_enemy_Boss->SetUnderTail(false);
//	m_enemy_Boss->SetisUnderPattern(false);
}
