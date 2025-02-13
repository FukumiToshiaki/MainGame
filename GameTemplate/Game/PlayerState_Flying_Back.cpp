#include "stdafx.h"
#include "PlayerState_Flying_Back.h"
#include "Player.h"

void PlayerState_Flying_Back::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Landing_Back, 0.2f
	);
}

void PlayerState_Flying_Back::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
	if (m_player->GetHP() <= 0) {
		m_player->ChangeState(Player::enState_Die);
	}
	//攻撃中にダメージを受けてモーションが中断した時に攻撃中の判定が出ないように
	m_player->SetisBitAttack(false);
	m_player->SetisGuradBreak(false);
	m_player->SetisWalkAttack(false);
	m_player->SetisLongAttack(false);
}
