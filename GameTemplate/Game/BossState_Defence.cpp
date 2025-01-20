#include "stdafx.h"
#include "BossState_Defence.h"
#include "Enemy_Boss.h"

void BossState_Defence::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Defence, 0.2f
	);
	if (m_enemy_Boss->GetIsPlayingAnimation() == false && m_defenceTime <= 0 ) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		m_defenceTime = rand() % 4;
		m_enemy_Boss->SetidUnderDefencePattern(false);
	}

}

void BossState_Defence::Update()
{
	m_defenceTime -= g_gameTime->GetFrameDeltaTime();
	m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
}
