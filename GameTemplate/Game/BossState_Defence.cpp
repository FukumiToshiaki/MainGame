#include "stdafx.h"
#include "BossState_Defence.h"
#include "Enemy_Boss.h"

void BossState_Defence::Animation()
{
	//アニメーション
	if (!m_isDefenseStart) {
		m_enemy_Boss->GetModelRender().PlayAnimation(
			Enemy_Boss::enState_Defence_Animation, 0.2f
		);
	}
	else {
		m_defenceTime -= g_gameTime->GetFrameDeltaTime();
	}
	//アニメーションが終わったら次の行動
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_isDefenseStart = true;
		m_enemy_Boss->GetModelRender().PlayAnimation(
			Enemy_Boss::enState_Defence_Counter_Animation, 0.2f
		);
	}
}

void BossState_Defence::Update()
{
	m_enemy_Boss->SetMoveSpeed(Vector3::Zero);
	m_enemy_Boss->SetMoveSpeed(m_enemy_Boss->GetDiff());
	//タイマーが0になったらIdle状態に
	if (m_defenceTime <= 0) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
		//次のディフェンスタイマーをセット
		m_defenceTime = rand() % 4;
		//ディフェンスの当たり判定を消す
		m_enemy_Boss->SetidUnderDefencePattern(false);
	}
}
