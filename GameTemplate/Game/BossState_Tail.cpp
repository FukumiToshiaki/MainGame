#include "stdafx.h"
#include "BossState_Tail.h"
#include "Enemy_Boss.h"

void BossState_Tail::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Tail, 0.2f
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->SetisTail(false);
	}
}

void BossState_Tail::Update()
{
	if (m_enemy_Boss->GetisDamage()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Damage);
		//m_enemy_Boss->SetisTail(false);
		//m_enemy_Boss->SetUnderTail(false);
	}
	if (!m_enemy_Boss->GetisTail()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
	m_enemy_Boss->SetUnderTail(false);
//	m_enemy_Boss->SetisUnderPattern(false);
}
