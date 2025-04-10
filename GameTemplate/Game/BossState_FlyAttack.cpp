#include "stdafx.h"
#include "BossState_FlyAttack.h"
#include "Enemy_Boss.h"

void BossState_FlyAttack::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Fly_Animation, 0.2f
	);
}

void BossState_FlyAttack::Update()
{
	m_flyAttackTime -= g_gameTime->GetFrameDeltaTime();
	//�^�C�}�[��0�ɂȂ�����
	if (m_flyAttackTime <= 0) {
		//�A�j���[�V����
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
		//���̃^�C�}�[���Z�b�g
		m_flyAttackTime = rand() % 3;
		//�U���̓����蔻��̃��Z�b�g
		m_enemy_Boss->SetisUnderFlyAttack(false);
	}

}
