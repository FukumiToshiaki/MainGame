#include "stdafx.h"
#include "BossState_Tail.h"
#include "Enemy_Boss.h"

void BossState_Tail::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Tail_Animation, 0.2f
	);
	//�A�j���[�V�������I�������
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}

void BossState_Tail::Update()
{
	//�ړ����x��0�ɂ���
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
}
