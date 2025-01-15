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
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Biting::Update()
{
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());

	//if (m_enemy_Boss->GetisDamage()) {
	//	m_enemy_Boss->ChangeState(Enemy_Boss::enState_Damage);
	//	//m_enemy_Boss->SetisBiting(false);
	//	m_enemy_Boss->SetUnderMelee(false);
	//}
	//m_enemy_Boss->SetisUnderPattern(false);
}
