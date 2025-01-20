#include "stdafx.h"
#include "PlayerState_Arching.h"
#include "Player.h"

void PlayerState_Arching::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Arching, 0.2f
	);
}


void PlayerState_Arching::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
	if (m_player->GetHP() <= 0) {
		m_player->ChangeState(Player::enState_Die);
	}

	//�U�����Ƀ_���[�W���󂯂ă��[�V���������f�������ɍU�����̔��肪�o�Ȃ��悤��
	m_player->SetisBitAttack(false);
	m_player->SetisGuradBreak(false);
	m_player->SetisWalkAttack(false);
	m_player->SetisLongAttack(false);

}
