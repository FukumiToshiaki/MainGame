#include "stdafx.h"
#include "PlayerState_Run.h"
#include "Player.h"

void PlayerState_Run::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Run, 0.2f
	);
}

void PlayerState_Run::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}
}
