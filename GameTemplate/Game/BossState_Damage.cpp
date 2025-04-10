#include "stdafx.h"
#include "BossState_Damage.h"
#include "Enemy_Boss.h"

void BossState_Damage::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Damage_Animation, 0.2f
	);
}

void BossState_Damage::Update()
{
	//�U�����Ƀ_���[�W���󂯂ă��[�V���������f�������ɍU�����̔��肪�o�Ȃ��悤��
	m_enemy_Boss->SetisUnderMelee(false);
	m_enemy_Boss->SetisUnderFlyAttack(false);
	m_enemy_Boss->SetisUnderTail(false);

	//HP��0�ɂȂ�����
	if (m_enemy_Boss->GetHP() <= 0) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Die);
	}
	//�A�j���[�V�������I������玟�̍s��
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
