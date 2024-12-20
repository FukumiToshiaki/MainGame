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
	if (!m_player->GetIsWalk()) {
		m_player->ChangeState(Player::enState_Idle);
	}
	if (m_player->GetIsWalkAttack()) {
		m_player->ChangeState(Player::enState_WalkAttack);
	}
	if (m_player->GetIsDefense()) {
		m_player->ChangeState(Player::enState_Defense);
	}
	if (m_player->GetIsGuradBreak()) {
		m_player->ChangeState(Player::enState_GuradBreak);
	}
	if (m_player->GetisDamage()) {
		m_player->ChangeState(Player::enState_Damage);
	}
	if (m_player->GetIsLongAttack()) {
		m_player->ChangeState(Player::enState_LongAttack);
	}

}
