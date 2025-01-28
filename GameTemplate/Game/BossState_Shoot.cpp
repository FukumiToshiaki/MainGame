#include "stdafx.h"
#include "BossState_Shoot.h"
#include "Enemy_Boss.h"

void BossState_Shoot::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Shoot_Animation,0.2f
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		//m_enemy_Boss->SetisUnderPattern(false);
	}

}

void BossState_Shoot::Update()
{
	m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
}
