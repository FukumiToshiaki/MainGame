#include "stdafx.h"
#include "BossState_Die.h"
#include "Enemy_Boss.h"

void BossState_Die::Animation()
{
	//�A�j���[�V����
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Die_Animation, 0.2f
	);
}

void BossState_Die::Update()
{
	//�Q�[���N���A
	m_enemy_Boss->SetisClear(true);
}
