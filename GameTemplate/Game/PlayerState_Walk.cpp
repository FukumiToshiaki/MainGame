#include "stdafx.h"
#include "PlayerState_Walk.h"
#include "Player.h"
void PlayerState_Walk::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Walk, 0.2f
	);
}

void PlayerState_Walk::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
}
