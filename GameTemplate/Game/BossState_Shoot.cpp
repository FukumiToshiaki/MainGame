#include "stdafx.h"
#include "BossState_Shoot.h"
#include "Enemy_Boss.h"

void BossState_Shoot::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Shoot,0.2f
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->SetisShoot(false);
		//m_enemy_Boss->SetisUnderPattern(false);
	}

}

void BossState_Shoot::Update()
{
	if (m_enemy_Boss->GetisDamage()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Damage);
	}

	if (!m_enemy_Boss->GetisShoot()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
