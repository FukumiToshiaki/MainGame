#include "stdafx.h"
#include "PlayerState_Idle.h"
#include "Player.h"

void PlayerState_Idle::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Idle, 0.2f
	);
}

void PlayerState_Idle::Update()
{

}
