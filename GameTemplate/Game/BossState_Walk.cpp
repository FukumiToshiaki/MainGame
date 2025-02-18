#include "stdafx.h"
#include "BossState_Walk.h"
#include "Enemy_Boss.h"

void BossState_Walk::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Move_Animation, 0.2f
	);
	if (m_walkTime <= 0.0f || !m_enemy_Boss->GetIsPlayingAnimation()) {
		// 次のステートに遷移する
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		m_walkTime = rand() % 4;
	}
}

void BossState_Walk::Update()
{
	m_walkTime -= g_gameTime->GetFrameDeltaTime();

	//if (!m_enemy_Boss->GetisDistance()) {
	//	m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	//}
	//if (m_enemy_Boss->GetisBiting()) {
	//	m_enemy_Boss->ChangeState(Enemy_Boss::enState_Attack_Biting);
	//}
	//if (m_enemy_Boss->GetisDamage()) {
	//	m_enemy_Boss->ChangeState(Enemy_Boss::enState_Damage);
	//}

}
