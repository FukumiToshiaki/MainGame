#include "stdafx.h"
#include "BossState_Fly.h"
#include "Enemy_Boss.h"

void BossState_Fly::Animation()
{
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Fly, 0.2f
	);
	if (m_flyTime<=0) {
		// 次のステートに遷移する
		m_enemy_Boss->ChangeState(m_enemy_Boss->enState_Landing);
		m_flyTime = rand() % 4;
	}
}

void BossState_Fly::Update()
{
	m_flyTime -= g_gameTime->GetFrameDeltaTime();

}
