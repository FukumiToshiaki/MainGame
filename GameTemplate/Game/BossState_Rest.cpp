#include "stdafx.h"
#include "BossState_Rest.h"
#include "Enemy_Boss.h"

void BossState_Rest::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Rest_Animation, 0.2f
	);
}

void BossState_Rest::Update()
{
	//���̎��Ԍv��
	m_time -= g_gameTime->GetFrameDeltaTime();
	//�^�C�}�[��0�ɂȂ�����A�j���[�V����
	if (m_time <= 0.0f) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
