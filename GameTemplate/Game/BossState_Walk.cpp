#include "stdafx.h"
#include "BossState_Walk.h"
#include "Enemy_Boss.h"

void BossState_Walk::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Move_Animation, 0.2f
	);
	//タイマーが0になる&アニメーションが終わったら
	if (m_walkTime <= 0.0f || !m_enemy_Boss->GetIsPlayingAnimation()) {
		// 次のステートに遷移する
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		//タイマーのリセット
		m_walkTime = rand() % 4;
	}
}

void BossState_Walk::Update()
{
	//タイマー開始
	m_walkTime -= g_gameTime->GetFrameDeltaTime();
}
