#include "stdafx.h"
#include "BossState_Damage.h"
#include "Enemy_Boss.h"

void BossState_Damage::Animation()
{
	//アニメーション
	m_enemy_Boss->GetModelRender().PlayAnimation(
		Enemy_Boss::enState_Damage_Animation, 0.2f
	);
}

void BossState_Damage::Update()
{
	//攻撃中にダメージを受けてモーションが中断した時に攻撃中の判定が出ないように
	m_enemy_Boss->SetisUnderMelee(false);
	m_enemy_Boss->SetisUnderFlyAttack(false);
	m_enemy_Boss->SetisUnderTail(false);

	//HPが0になったら
	if (m_enemy_Boss->GetHP() <= 0) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Die);
	}
	//アニメーションが終わったら次の行動
	if (!m_enemy_Boss->GetIsPlayingAnimation()) {
		m_enemy_Boss->ChangeState(Enemy_Boss::enState_Idle);
	}
}
