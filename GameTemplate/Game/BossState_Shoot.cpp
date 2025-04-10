#include "stdafx.h"
#include "BossState_Shoot.h"
#include "Enemy_Boss.h"

void BossState_Shoot::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Shoot_Animation,0.2f
	);
}

void BossState_Shoot::Update()
{
	//�ړ����x��0�ɂ���
	m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
	//�A�j���[�V�������I�������
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
