#include "stdafx.h"
#include "BossState_Fly.h"
#include "Enemy_Boss.h"

void BossState_Fly::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Fly_Animation, 0.2f
	);
}

void BossState_Fly::Update()
{
	//���ł��鎞��
	m_flyTime -= g_gameTime->GetFrameDeltaTime();
	//�^�C�}�[��0�ɂȂ�����
	if (m_flyTime <= 0) {
		// ���̃X�e�[�g�ɑJ�ڂ���
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
		m_flyTime = rand() % 4;
	}

}
