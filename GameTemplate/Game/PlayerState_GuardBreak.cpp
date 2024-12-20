#include "stdafx.h"
#include "PlayerState_GuardBreak.h"
#include "Player.h"

void PlayerState_GuardBreak::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_GuardBreak, 0.2f
	);
	if (m_player->GetIsPlayingAnimation() == false) {
		m_player->SetIsGuradBreak(false);
	}
}

void PlayerState_GuardBreak::Update()
{
	if (!m_player->GetIsGuradBreak()) {
		m_player->ChangeState(Player::enState_Idle);
	}
}
