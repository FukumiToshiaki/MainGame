#include "stdafx.h"
#include "PlayerState_Die.h"
#include "Player.h"

void PlayerState_Die::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Die, 0.2f
	);
}

void PlayerState_Die::Update()
{
	m_player->SetisOver(true);
}
