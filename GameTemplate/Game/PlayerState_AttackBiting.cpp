#include "stdafx.h"
#include "PlayerState_AttackBiting.h"
#include "Player.h"
void PlayerState_AttackBiting::Animation()
{
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_Attack, 0.2f
	);
}

void PlayerState_AttackBiting::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->SetisBitAttack(false);
		m_player->ChangeState(Player::enState_Idle);
	}
}
