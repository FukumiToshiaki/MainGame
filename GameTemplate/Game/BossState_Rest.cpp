#include "stdafx.h"
#include "BossState_Rest.h"
#include "Enemy_Boss.h"

void BossState_Rest::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Rest_Animation, 0.2f
	);
	if (m_time<=0.0f) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}

}

void BossState_Rest::Update()
{
	//Œ„‚ÌŽžŠÔŒv‘ª
	m_time -= g_gameTime->GetFrameDeltaTime();

}
