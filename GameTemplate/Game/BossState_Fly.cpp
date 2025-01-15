#include "stdafx.h"
#include "BossState_Fly.h"
#include "Enemy_Boss.h"

void BossState_Fly::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Fly, 0.2f
	);
	if (m_enemy_Boss->GetFlyTime()<=0) {
		// 次のステートに遷移する
		m_enemy_Boss->ChangeState(m_enemy_Boss->enState_Landing);
	}
}

void BossState_Fly::Update()
{
}
