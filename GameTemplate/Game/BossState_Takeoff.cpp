#include "stdafx.h"
#include "BossState_Takeoff.h"
#include "Enemy_Boss.h"

void BossState_Takeoff::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Takeoff, 0.2f
	);
	if (m_enemy_Boss->GetIsPlayingAnimation() == false && m_enemy_Boss->GetisTakeoff()) {
		m_enemy_Boss->SetisFly(true);
		m_enemy_Boss->SetisTakeoff(false);
	}
}

void BossState_Takeoff::Update()
{
	if (m_enemy_Boss->GetisFly()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Fly);
	}
}
