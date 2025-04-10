#include "stdafx.h"
#include "BossState_FlyAttack.h"
#include "Enemy_Boss.h"

void BossState_FlyAttack::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Attack_Fly_Animation, 0.2f
	);
}

void BossState_FlyAttack::Update()
{
	m_flyAttackTime -= g_gameTime->GetFrameDeltaTime();
	//タイマーが0になったら
	if (m_flyAttackTime <= 0) {
		//アニメーション
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Landing);
		//次のタイマーをセット
		m_flyAttackTime = rand() % 3;
		//攻撃の当たり判定のリセット
		m_enemy_Boss->SetisUnderFlyAttack(false);
	}

}
