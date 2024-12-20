#include "stdafx.h"
#include "PlayerState_WalkAttack.h"
#include "Player.h"

void PlayerState_WalkAttack::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_WalkAttack, 0.2f
	);
	if (m_player->GetIsPlayingAnimation() == false) {
		m_player->SetIsWalkAttack(false);
	}
}

void PlayerState_WalkAttack::Update()
{
	if (!m_player->GetIsWalkAttack())
	{
		m_player->ChangeState(Player::enState_Idle);
	}
}
