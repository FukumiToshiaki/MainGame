#include "stdafx.h"
#include "BossState_Fly.h"
#include "Enemy_Boss.h"

void BossState_Fly::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Fly, 0.2f
	);
	if (/*m_enemy_Boss->GetIsPlayingAnimation() == false &&*/ m_enemy_Boss->GetisFly()) {
		//m_enemy_Boss->SetisLanding(true);
		//m_enemy_Boss->SetisFlyAttack(true);
		m_enemy_Boss->SetisFlyShoot(true);
	}
}

void BossState_Fly::Update()
{
	//if (m_enemy_Boss->GetisFlyAttack()) {
	//	m_enemy_Boss->ChangeState(Enemy_Boss::enState_Attack_Fly);
	//	m_enemy_Boss->SetisFly(false);
	//}
	if (m_enemy_Boss->GetisFlyShoot()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Attack_FlyShoot);
	}
	//if (m_enemy_Boss->GetisLanding()) {
	//	m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
	//}
	m_enemy_Boss->SetisFly(false);
}
