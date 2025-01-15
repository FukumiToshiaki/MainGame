#include "stdafx.h"
#include "BossState_Takeoff.h"
#include "Enemy_Boss.h"

void BossState_Takeoff::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Takeoff, 0.2f
	);
	if (m_enemy_Boss->GetIsPlayingAnimation() == false) {
		// 次のステートに遷移する
		m_enemy_Boss->ChangeState((Enemy_Boss::EnState)m_enNextState);
	}
}

void BossState_Takeoff::Update()
{
}
