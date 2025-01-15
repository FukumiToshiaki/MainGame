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
}
