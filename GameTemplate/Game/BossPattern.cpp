#include "stdafx.h"
#include "BossPattern.h"
#include "Enemy_Boss.h"
#include "Player.h"

#include "math.h"
#include <numeric>

#define DISTANCE_POS 1400.0f
#define FIRST_PHASE 8
#define SECOND_PHASE 6
#define FINAL_PHASE 4
#define MELEE_ATTACK 0
#define TAIL_ATTACK 13
#define FLY 20
#define SHOOT_ATTACK 17
#define MELEE_POINT 25
#define ATTACK_COOLTIME 6.0f
#define MELEE_DISTANCE 550.0f
#define CHASE_SPEED 200.0f

BossPattern::~BossPattern()
{
	
}

bool BossPattern::Start()
{
	Enemy_Boss::Start();
	//m_enemy_Boss = FindGO<Enemy_Boss>("enemy_boss");
	m_player = FindGO<Player>("player");
	return true;
}

void BossPattern::Update()
{
	CoolTime();
	MeleePattern();
	Melee();
	// 基底クラスのUpdateを呼ぶ
	Enemy_Boss::Update();
}

void BossPattern::CoolTime()
{
	//0秒になっているなら計算する必要ない
	if (m_isUnderPattern) {
		return;
	}
	m_meleeAttackCoolTime -= g_gameTime->GetFrameDeltaTime();

	//0秒になったらフラグを立てる
	if (m_meleeAttackCoolTime <= 0.0f) {
		m_isUnderPattern = true;
	}
}

int BossPattern::MeleePattern()
{
	//int actions[] = { m_meleeAttack,m_shoot,m_defend,m_fly,m_tailAttack };
	//int n = sizeof(actions) / sizeof(actions[0]);
	//int total_weight = std::accumulate(actions, actions + n, 0);
	//m_meleeAttackCoolTime -= g_gameTime->GetFrameDeltaTime();
	//int rand_val = rand() % total_weight;
	//int sum = 0;
	//for (int Last = 0;  < ; Last++)
	//{

	//}

	//プレイヤーの追跡の変数
	m_distance = m_player->Get_PlayerPos() - m_pos;
	m_diff = m_player->Get_PlayerPos() - m_pos;
	m_diff.Normalize();
	if (m_distance.Length() <= MELEE_DISTANCE) {
		m_isDistance = false;
	}
	//プレイヤーとの距離が一定以下なら追跡　遠距離攻撃フラグを無しに
	else if (m_distance.Length() <= DISTANCE_POS) {
		m_isDistance = true;
		m_isShoot = false;
		m_moveSpeed = m_diff * CHASE_SPEED;
	}
	else {
		m_shootStandTime -= g_gameTime->GetFrameDeltaTime();
	}
	if (m_isUnderPattern && m_distance.Length() <= MELEE_DISTANCE) {
		//第1段階
		if (m_testHP > FIRST_PHASE) {
			return 0;
		}
		//第2段階
		else if (m_testHP > SECOND_PHASE) {
			return 1;
		}
		//第3段階
		else if (m_testHP > FINAL_PHASE) {
			return 2;
		}
		//第4段階
		else {
			return 3;
		}
	}
}

void BossPattern::Melee()
{
	//フラグが立っていないなら計算する必要がないので、早期リターン
	if (!m_isUnderPattern) {
		return;
	}

	m_meleePoint = this->MeleePattern();

	//体力によってランダムの数字が変わる
	switch (m_meleePoint)
	{
	case 0:
		m_attack_Rand += 5;
		break;
	case 1:
		m_attack_Rand += 8;
		break;
	case 2:
		m_attack_Rand += 12;
		break;
	case 3:
		m_attack_Rand += 15;
		break;
	}

	m_attack_Rand += rand() % 10;

	if (m_attack_Rand >= FLY) {
		m_isFly = true;
	}
	else if (m_attack_Rand >= SHOOT_ATTACK) {
		m_isShoot = true;
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_moveSpeed = m_diff;
		m_isDistance = false;
	}
	else if (m_attack_Rand >= TAIL_ATTACK) {
		m_isTail = true;
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_moveSpeed = m_diff;
		m_isDistance = false;
	}
	else {
		m_isBiting = true;
		m_moveSpeed = { 0.0f,0.0f,0.0f };
		m_isDistance = false;
		m_moveSpeed = m_diff;
	}

	m_meleeAttackCoolTime = ATTACK_COOLTIME;
	m_attack_Rand = 0;
	m_isUnderPattern = false;
	////0なら距離をとる
	//if (m_attack_Rand == 0) {
	//	m_isTakeoff = true;
	//	m_isUnderPattern = true;
	//}
	////尻尾攻撃
	//else if (m_attack_Rand == 1 || m_attack_Rand == 2
	//	|| m_attack_Rand == 6) {
	//	m_isTail = true;
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_isDistance = false;
	//	m_moveSpeed = m_diff;
	//	m_isUnderPattern = true;
	//}
	////噛みつき攻撃
	//else if (m_attack_Rand == 3 || m_attack_Rand == 4
	//	|| m_attack_Rand == 5 || m_attack_Rand == 7
	//	|| m_attack_Rand == 8 || m_attack_Rand == 9)
	//{
	//	m_isBiting = true;
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_isDistance = false;
	//	m_moveSpeed = m_diff;
	//	m_isUnderPattern = true;
	//}

}

//int BossPattern::LongPattern()
//{
//	if (m_shootStandTime <= 0.0f) {
//		if (m_testHP > FIRST_PHASE) {
//			return 0;
//		}
//		//第2段階
//		else if (m_testHP > SECOND_PHASE) {
//			return 1;
//		}
//		//第3段階
//		else if (m_testHP > FINAL_PHASE) {
//			return 2;
//		}
//		//第4段階
//		else {
//			return 3;
//		}
//		m_shootStandTime = ATTACK_COOLTIME;
//	}
//}

//void BossPattern::Long()
//{
//	m_shootPoint = this->LongPattern();
//	switch (m_shootPoint)
//	{
//	case 0:
//		m_attack_Rand = rand() % 10;
//		break;
//	case 1:
//		m_attack_Rand = rand() % 8;
//		break;
//	case 2:
//		m_attack_Rand = rand() % 6;
//		break;
//	case 3:
//		m_attack_Rand = rand() % 4;
//		break;
//	}
//
//	if (m_attack_Rand == 0) {
//
//	}
//}

