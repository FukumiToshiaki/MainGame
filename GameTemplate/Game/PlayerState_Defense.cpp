#include "stdafx.h"
#include "PlayerState_Defense.h"
#include "Player.h"

void PlayerState_Defense::Animation()
{
	m_isDefenseStart = true;
	m_player->GetModelRender().PlayAnimation(
		Player::enAnimClip_DefenceStart, 0.2f
	);
	if (m_player->GetIsPlayingAnimation() == false && m_isDefenseStart) {
		m_player->GetModelRender().PlayAnimation(
			Player::enAnimClip_Defense, 0.2f
		);
		m_isDefense = true;
	}
	if (m_player->GetIsPlayingAnimation() == false && m_isDefense) {
		m_player->GetModelRender().PlayAnimation(
			Player::enAnimClip_DefenceEnd, 0.2f
		);
		m_isDefenseEnd = true;
	}
}

void PlayerState_Defense::Update()
{
	if (!m_player->GetIsPlayingAnimation()) {
		m_player->ChangeState(Player::enState_Idle);
	}

	//下の処理はアニメーションのブールを戻す
	if (m_isDefenseEnd) {
		m_isDefenseStart = false;		
		m_isDefense = false;
		m_isDefenseEnd = false;
	}
}
