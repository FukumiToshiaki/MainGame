#include "stdafx.h"
#include "BossState_Fly.h"
#include "Enemy_Boss.h"

void BossState_Fly::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Fly_Animation, 0.2f
	);
}

void BossState_Fly::Update()
{
	//飛んでいる時間
	m_flyTime -= g_gameTime->GetFrameDeltaTime();
	//タイマーが0になったら
	if (m_flyTime <= 0) {
		// 次のステートに遷移する
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
		m_flyTime = rand() % 4;
	}

}
