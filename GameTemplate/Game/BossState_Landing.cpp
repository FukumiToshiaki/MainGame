#include "stdafx.h"
#include "BossState_Landing.h"
#include "Enemy_Boss.h"

void BossState_Landing::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Landing_Animation, 0.2f
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation())
	{
		//���K�p
		m_enemy_Boss->SetisScream_Normal(true);
		//Idle��Ԃɂ���
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Landing::Update()
{

}
