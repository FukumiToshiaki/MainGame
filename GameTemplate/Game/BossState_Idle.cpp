#include "stdafx.h"
#include "BossState_Idle.h"
#include "Enemy_Boss.h"

void BossState_Idle::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Idle,0.2f
	);

}

void BossState_Idle::Update()
{
	if (m_enemy_Boss->GetisDistance()&&!m_enemy_Boss->GetisBiting()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Move);
	}
	if (m_enemy_Boss->GetisBiting()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Attack_Biting);
	}
	if (m_enemy_Boss->GetisShoot()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Attack_Shoot);
	}
	if (m_enemy_Boss->GetisDamage()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Damage);
	}
	if (m_enemy_Boss->GetisTail()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Attack_Tail);
	}
	if (m_enemy_Boss->GetisTakeoff()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Takeoff);
	}
	if (m_enemy_Boss->GetisScream()){
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Attack_Scream);
	}
	m_enemy_Boss->SetisIdle(false);
}
