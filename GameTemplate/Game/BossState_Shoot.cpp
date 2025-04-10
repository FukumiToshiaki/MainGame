#include "stdafx.h"
#include "BossState_Shoot.h"
#include "Enemy_Boss.h"

void BossState_Shoot::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Shoot_Animation,0.2f
	);
}

void BossState_Shoot::Update()
{
	//移動速度を0にする
	m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
	//アニメーションが終わったら
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
