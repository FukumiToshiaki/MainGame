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
	if (m_player->GetisDamage()) {
		m_player->ChangeState(Player::enState_Damage);
	}
	if (m_player->GetIsAttack_Biting()) {
		m_player->ChangeState(Player::enState_Attack_Biting);
	}
	if (m_player->GetIsWalk()) {
		m_player->ChangeState(Player::enState_Walk);
	}
	if (m_player->GetIsDefense()) {
		m_player->ChangeState(Player::enState_Defense);
	}
	if (m_player->GetIsGuradBreak()) {
		m_player->ChangeState(Player::enState_GuradBreak);
	}
	if (m_player->GetIsLongAttack()) {
		m_player->ChangeState(Player::enState_LongAttack);
	}
}
