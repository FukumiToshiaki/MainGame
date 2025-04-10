#include "stdafx.h"
#include "BossState_Tail.h"
#include "Enemy_Boss.h"

void BossState_Tail::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Tail_Animation, 0.2f
	);
	//アニメーションが終わったら
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Tail::Update()
{
	//移動速度を0にする
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
}
