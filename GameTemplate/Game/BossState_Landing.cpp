#include "stdafx.h"
#include "BossState_Landing.h"
#include "Enemy_Boss.h"

void BossState_Landing::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Landing_Animation, 0.2f
	);
	if (m_enemy_Boss->GetisScream_Set() && !m_enemy_Boss->GetIsPlayingAnimation()) {
		//™ôšK—p
		m_enemy_Boss->SetisScream_Normal(true);
	}
	else if (!m_enemy_Boss->GetIsPlayingAnimation())
	{
		//Idleó‘Ô‚É‚·‚é
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Landing::Update()
{
}
