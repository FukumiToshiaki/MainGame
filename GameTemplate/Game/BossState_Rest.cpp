#include "stdafx.h"
#include "BossState_Rest.h"
#include "Enemy_Boss.h"

void BossState_Rest::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Rest_Animation, 0.2f
	);
}

void BossState_Rest::Update()
{
	//隙の時間計測
	m_time -= g_gameTime->GetFrameDeltaTime();
	//タイマーが0になったらアニメーション
	if (m_time <= 0.0f) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
