#include "stdafx.h"
#include "PlayerState_WalkAttack.h"
#include "Player.h"

void PlayerState_WalkAttack::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_WalkAttack, 0.2f
	);
}

void PlayerState_WalkAttack::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
}
