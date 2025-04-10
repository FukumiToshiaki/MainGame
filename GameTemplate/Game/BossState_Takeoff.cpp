#include "stdafx.h"
#include "BossState_Takeoff.h"
#include "Enemy_Boss.h"

void BossState_Takeoff::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Takeoff_Animation, 0.2f
	);
	//アニメーションが終わったら
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		// 次のステートに遷移する
		m_enemy_Boss->ChangeState((Enemy_Boss::EnState)m_enNextState);
	}
	//咆哮ができるようになったら咆哮のできる位置に移動する
	if (m_enemy_Boss->GetisScream_Set()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Fly);
	}

}

void BossState_Takeoff::Update()
{
}
