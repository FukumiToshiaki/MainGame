#include "stdafx.h"
#include "BossState_Defence.h"
#include "Enemy_Boss.h"

void BossState_Defence::Animation()
{
	//�A�j���[�V����
	if (!m_isDefenseStart) {
		m_enemy_Boss->GetModelRender().PlayAnimation(
			Enemy_Boss::enState_Defence_Animation, 0.2f
		);
	}
	else {
		m_defenceTime -= g_gameTime->GetFrameDeltaTime();
	}
	//�A�j���[�V�������I������玟�̍s��
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_isDefenseStart = true;
		m_enemy_Boss->GetModelRender().PlayAnimation(
			Enemy_Boss::enState_Defence_Counter_Animation, 0.2f
		);
	}
}

void BossState_Defence::Update()
{
	m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
	//�^�C�}�[��0�ɂȂ�����Idle��Ԃ�
	if (m_defenceTime <= 0) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		//���̃f�B�t�F���X�^�C�}�[���Z�b�g
		m_defenceTime = rand() % 4;
		//�f�B�t�F���X�̓����蔻�������
		m_enemy_Boss->SetidUnderDefencePattern(false);
	}
}
