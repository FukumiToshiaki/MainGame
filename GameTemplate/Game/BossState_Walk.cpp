#include "stdafx.h"
#include "BossState_Walk.h"
#include "Enemy_Boss.h"

void BossState_Walk::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Move_Animation, 0.2f
	);
	//�^�C�}�[��0�ɂȂ�&�A�j���[�V�������I�������
	if (m_walkTime <= 0.0f || !m_enemy_Boss->GetIsPlayingAnimation()) {
		// ���̃X�e�[�g�ɑJ�ڂ���
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		//�^�C�}�[�̃��Z�b�g
		m_walkTime = rand() % 4;
	}
}

void BossState_Walk::Update()
{
	//�^�C�}�[�J�n
	m_walkTime -= g_gameTime->GetFrameDeltaTime();
}
