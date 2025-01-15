#include "stdafx.h"
#include "PlayerState_Damage.h"
#include "Player.h"

void PlayerState_Damage::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Damage, 0.2f
	);
}

void PlayerState_Damage::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
	if (m_player->GetHP() <= 0) {
		m_player->ChangeState(Player::enState_Die);
	}
}
