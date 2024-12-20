#include "stdafx.h"
#include "BossState_Biting.h"
#include "Enemy_Boss.h"
#include "Player.h"

void BossState_Biting::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Biting,0.2f
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->SetisBiting(false);
	}
}

void BossState_Biting::Update()
{
	if (!m_enemy_Boss->GetisBiting()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		//m_enemy_Boss->SetisBiting(false);
		m_enemy_Boss->SetUnderMelee(false);

	}

	if (m_enemy_Boss->GetisDistance()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Move);
		//m_enemy_Boss->SetisBiting(false);
		m_enemy_Boss->SetUnderMelee(false);

	}
	if (m_enemy_Boss->GetisDamage()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Damage);
		//m_enemy_Boss->SetisBiting(false);
		m_enemy_Boss->SetUnderMelee(false);
	}
	//m_enemy_Boss->SetisUnderPattern(false);
}
