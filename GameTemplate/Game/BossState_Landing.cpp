#include "stdafx.h"
#include "BossState_Landing.h"
#include "Enemy_Boss.h"

void BossState_Landing::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Landing_Animation, 0.2f
	);
}

void BossState_Landing::Update()
{
	if (m_enemy_Boss->GetisScream_Set() && !m_enemy_Boss->GetIsPlayingAnimation()) {
		//咆哮用
		m_enemy_Boss->SetisScream_Normal(true);
	}
	else if (!m_enemy_Boss->GetIsPlayingAnimation())
	{
		//Idle状態にする
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
