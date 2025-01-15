#include "stdafx.h"
#include "PlayerState_GuardBreak.h"
#include "Player.h"

void PlayerState_GuardBreak::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_GuardBreak, 0.2f
	);
}

void PlayerState_GuardBreak::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
}
