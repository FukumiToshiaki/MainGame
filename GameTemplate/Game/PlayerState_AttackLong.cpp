#include "stdafx.h"
#include "PlayerState_AttackLong.h"
#include "Player.h"

void PlayerState_AttackLong::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_LongAttack, 0.2f
	);
}

void PlayerState_AttackLong::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
}
