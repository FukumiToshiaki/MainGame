#include "stdafx.h"
#include "BossState_Idle.h"
#include "Enemy_Boss.h"

void BossState_Idle::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Idle_Animation,0.2f
	);

}

void BossState_Idle::Update()
{
	m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
}
