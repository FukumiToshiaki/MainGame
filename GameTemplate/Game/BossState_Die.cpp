#include "stdafx.h"
#include "BossState_Die.h"
#include "Enemy_Boss.h"

void BossState_Die::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Die, 0.2f
	);
}

void BossState_Die::Update()
{
	m_enemy_Boss->SetisClear(true);
}
