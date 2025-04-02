#include "stdafx.h"
#include "BossState_Biting.h"
#include "Enemy_Boss.h"
#include "Player.h"

void BossState_Biting::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Biting_Animation,0.2f
	);
	//�A�j���[�V�������I������玟�̍s��
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Biting::Update()
{
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
}
