#include "stdafx.h"
#include "BossState_Rest.h"
#include "Enemy_Boss.h"

void BossState_Rest::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Rest
	);
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->SetisRest(false);
	}

}

void BossState_Rest::Update()
{
}
