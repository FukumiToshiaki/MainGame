#include "stdafx.h"
#include "BossState_Damage.h"
#include "Enemy_Boss.h"

void BossState_Damage::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Damage, 0.2f
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->SetisDamage(false);
	}
}

void BossState_Damage::Update()
{
	if (!m_enemy_Boss->GetisDamage()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
	if (m_enemy_Boss->GetisDie()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Die);
	}
}
