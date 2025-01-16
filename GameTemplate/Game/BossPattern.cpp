#include "stdafx.h"
#include "BossPattern.h"
#include "Enemy_Boss.h"
#include "Player.h"

#include "math.h"
#include <numeric>

#define DISTANCE_POS 12000.0f
#define FIRST_PHASE 8
#define SECOND_PHASE 6
#define FINAL_PHASE 4
#define MELEE_ATTACK 0
#define TAIL_ATTACK 13
#define FLY 20
#define MELEE_SHOOT_ATTACK 17
#define MELEE_POINT 25
#define ATTACK_COOLTIME 5.0f
#define LASTATTACK_COOLTIME 4.0f
#define MELEE_DISTANCE 1500.0f
#define CHASE_SPEED 10.0f

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
	// 基底クラスのUpdateを呼ぶ
	Enemy_Boss::Update();

	//if (m_state == enState_Idle && m_player->GetHP() < 3) {
	//	m_coolTime = LASTATTACK_COOLTIME;
	//}
	//else if (m_state == enState_Idle && m_testHP < 3) {
	//	m_coolTime = LASTATTACK_COOLTIME;
	//}
	//else {
	//	m_coolTime = ATTACK_COOLTIME;
	//}

	CoolTime();

	BossPatternMode();
	DistancePattern();
	//フラグが立っていないなら計算する必要がないので、早期リターン
	if (!m_isUnderPattern) {
		return;
	}

	if (m_player->GetHP() < 3) {
		AttackModeLast();
			m_attack_Rand = 0;
			m_isUnderPattern = false;
			m_coolTime = LASTATTACK_COOLTIME;
		return;
	}
	else if (m_testHP < 3) {
		DefenseModeLast();
			m_attack_Rand = 0;
			m_isUnderPattern = false;
			m_coolTime = LASTATTACK_COOLTIME;
		return;
	}

	switch (m_pattern)
	{
	case -2:
		SuperDefenseMode();
		break;
	case -1:
		DefenseMode();
		break;
	case 0:
		NormalMode();
		break;
	case 1:
		AttackMode();
		break;
	case 2:
		SuperAttackMode();
		break;
	}
	m_attack_Rand = 0;
	m_isUnderPattern = false;
	m_coolTime = ATTACK_COOLTIME;
	//MeleePattern();
	//LongPattern();
	////trueなら近距離に行く
	//if (m_isBifurcation) {
	//	Melee();
	//}
	////falseなら遠距離に行く
	//else {
	//	Long();
	//}
	
}

void BossPattern::CoolTime()
{
	if (m_state == enState_Idle) {
		m_istest = true;
	}

	//0秒になっているなら計算する必要ない
	if (m_isUnderPattern) {
		return;
	}
	if (m_istest) {
		m_coolTime -= g_gameTime->GetFrameDeltaTime();
	}
	//発狂モード
	if (m_coolTime <= 0.0f && m_state == enState_Idle) {
		m_isUnderPattern = true;
		m_istest = false;
	}

	if (m_player->GetHP() < 3 || m_testHP < 3) {
		return;
	}
	//ここから下は通常モード

	//0秒になったらフラグを立てる
	if (m_coolTime <= 0.0f) {
		m_isUnderPattern = true;
		m_istest = false;
	}
}

void BossPattern::DistancePattern()
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
	if (m_distance.Length() <= DISTANCE_POS && m_state == enState_Move) {
		m_moveSpeed = m_diff * CHASE_SPEED;
	}
	//if (m_isUnderPattern && m_distance.Length() <= MELEE_DISTANCE) {
	//	m_isDistance = false;
	//	//trueなら近距離
	//	m_isBifurcation = true;
	//	//第1段階
	//	if (m_testHP > FIRST_PHASE) {
	//		return 0;
	//	}
	//	//第2段階
	//	else if (m_testHP > SECOND_PHASE) {
	//		return 1;
	//	}
	//	//第3段階
	//	else if (m_testHP > FINAL_PHASE) {
	//		return 2;
	//	}
	//	//第4段階
	//	else {
	//		return 3;
	//	}
	//}
	////プレイヤーとの距離が一定以下なら追跡　遠距離攻撃フラグを無しに
	//else if (m_distance.Length() <= DISTANCE_POS) {
	//	m_isDistance = true;
	//	m_isShoot = false;
	//	m_moveSpeed = m_diff * CHASE_SPEED;
	//}
	//else {
	//	m_shootStandTime -= g_gameTime->GetFrameDeltaTime();
	//}
}

void BossPattern::AttackModeLast()
{
	//フラグが立っていないなら計算する必要がないので、早期リターン
	if (!m_isUnderPattern) {
		return;
	}
	if (m_testHP >= 3) {
		return;
	}
	//m_meleePoint = this->MeleePattern();
	//体力によってランダムの数字が変わる
	//switch (m_meleePoint)
	//{
	//case 0:
	//	m_attack_Rand += 5;
	//	break;
	//case 1:
	//	m_attack_Rand += 8;
	//	break;
	//case 2:
	//	m_attack_Rand += 12;
	//	break;
	//case 3:
	//	m_attack_Rand += 15;
	//	break;
	//}
	//m_attack_Rand += rand() % 10;
	//if (m_attack_Rand >= FLY) {
	//	//m_isTakeoff = true;
	//}
	//else if (m_attack_Rand >= MELEE_SHOOT_ATTACK) {
	//	m_isShoot = true;
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_moveSpeed = m_diff;
	//	m_isDistance = false;
	//}
	//else if (m_attack_Rand >= TAIL_ATTACK) {
	//	m_isTail = true;
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_moveSpeed = m_diff;
	//	m_isDistance = false;
	//}
	//else {
	//	m_isBiting = true;
	//	m_moveSpeed = { 0.0f,0.0f,0.0f };
	//	m_isDistance = false;
	//	m_moveSpeed = m_diff;
	//}
	//m_meleeAttackCoolTime = ATTACK_COOLTIME;
	//m_attack_Rand = 0;
	//m_isUnderPattern = false;
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

		//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//13以上なら距離をとる
		if (m_attack_Rand >= 13) {
			ChangeState(Enemy_Boss::enState_Takeoff);
		}
		//11以上ならガード
		else if (m_attack_Rand >= 11) {
			ChangeState(Enemy_Boss::enState_Defence);
		}
		//7以上なら噛みつき
		else if (m_attack_Rand >= 7) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//4以上ならブレス
		else if (m_attack_Rand >= 4) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//4未満なら尻尾攻撃
		else {
			ChangeState(Enemy_Boss::enState_Attack_Tail);
		}
	}
	//falseなら遠距離パターンに
	else {
		////12以上なら空ブレス
		//if (m_attack_Rand >= 12) {
		//	ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		//}
		//9以上なら滑空突進
		//else 
			if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		////6以上ならブレス
		//else if (m_attack_Rand >= 6) {
		//	ChangeState(Enemy_Boss::enState_Attack_Shoot);
		//}
		////6未満なら近づく
		//else {
		//	ChangeState(Enemy_Boss::enState_Move);
		//}
	}
}

void BossPattern::DefenseModeLast()
{
	//if (m_shootStandTime <= 0.0f) {
	//	m_isBifurcation = false;
	//	if (m_testHP > FIRST_PHASE) {
	//		return 0;
	//	}
	//	//第2段階
	//	else if (m_testHP > SECOND_PHASE) {
	//		return 1;
	//	}
	//	//第3段階
	//	else if (m_testHP > FINAL_PHASE) {
	//		return 2;
	//	}
	//	//第4段階
	//	else {
	//		return 3;
	//	}
	//}
		//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//9以上なら距離をとる
		if (m_attack_Rand >= 0) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Fly);
		}
		////7以上なら嚙みつき
		//else if (m_attack_Rand >= 7) {
		//	ChangeState(Enemy_Boss::enState_Attack_Biting);
		//}
		////5以上ならブレス
		//else if (m_attack_Rand >= 5) {
		//	ChangeState(Enemy_Boss::enState_Attack_Shoot);
		//}
		////2以上ならガード
		//else if (m_attack_Rand >= 2) {
		//	ChangeState(Enemy_Boss::enState_Defence);
		//}
		////2未満なら尻尾攻撃
		//else {
		//	ChangeState(Enemy_Boss::enState_Attack_Tail);
		//}
	}
	//falseなら遠距離パターンに
	else {
		////9以上なら空ブレス
		//if (m_attack_Rand >= 8) {
		//	ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		//}
		////5以上なら滑空突進
		//else 
		if (m_attack_Rand >= 6) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		////1以上ならブレス
		//else if (m_attack_Rand >= 1) {
		//	ChangeState(Enemy_Boss::enState_Attack_Shoot);
		//}
		//1未満なら近づく
		//else {
		//	ChangeState(Enemy_Boss::enState_Move);
		//}
	}
}

//void BossPattern::Long()
//{
//
//	//フラグが立っていないなら計算する必要がないので、早期リターン
//	if (!m_isUnderPattern) {
//		return;
//	}
//
//	switch (m_shootPoint)
//	{
//	case 0:
//		m_attack_Rand += 12;
//		break;
//	case 1:
//		m_attack_Rand += 13;
//		break;
//	case 2:
//		m_attack_Rand += 14;
//		break;
//	case 3:
//		m_attack_Rand += 16;
//		break;
//	}
//
//	m_attack_Rand += rand() % 10;
//
//	//FLY以上なら空を飛び、別パターンに入る
//	if (m_attack_Rand >= FLY) {
//		//m_isTakeoff = true;
//	}
//	//FLY以下なら遠距離から攻撃する
//	else {
//			m_moveSpeed = { 0.0f,0.0f,0.0f };
//			m_isDistance = false;
//			m_isShoot = true;
//			m_moveSpeed = m_diff;
//	}
//	m_coolTime = ATTACK_COOLTIME;
//	m_attack_Rand = 0;
//	m_isUnderPattern = false;
//
//}

int BossPattern::BossPatternMode()
{
	if (m_isUnderPattern) {
		ChangeState(Enemy_Boss::enState_Move);
		//距離内なら近距離型のtrueに
		if (m_distance.Length() <= MELEE_DISTANCE) {
			m_isBifurcation = true;
		}
		//違うなら遠距離型のfalseに
		else {
			m_isBifurcation = false;
		}
		//第1段階
		if (m_testHP > FIRST_PHASE) {
			m_attack_Rand += rand() % 3;
		}
		//第2段階
		else if (m_testHP > SECOND_PHASE) {
			m_attack_Rand += rand() % 4;
		}
		//第3段階
		else if (m_testHP > FINAL_PHASE) {
			m_attack_Rand += rand() % 5;
		}
		//第4段階
		else {
			m_attack_Rand += rand() % 6;
		}

		//PlayerのHPが多かったら足す数字を少なく、
		//少なかったら足す数字を大きく
		if (m_player->GetHP() > FIRST_PHASE) {
			m_attack_Rand += rand() % 2;
		}
		else if (m_player->GetHP() > SECOND_PHASE) {
			m_attack_Rand += rand() % 3;
		}
		else if (m_player->GetHP() > FINAL_PHASE) {
			m_attack_Rand += rand() % 5;
		}
		else {
			m_attack_Rand += rand() % 6;
		}
		m_attack_Rand += rand() % 5;
		
		return true;
	}
}

void BossPattern::SuperDefenseMode()
{
	//m_attack_Rand = this->BossPatternMode();
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//11以上なら距離をとる
		if (m_attack_Rand >= 11) {
			ChangeState(Enemy_Boss::enState_Takeoff);
		}
		//9以上なら嚙みつき
		else if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//7以上ならブレス
		else if (m_attack_Rand >= 7) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//4以上ならガード
		else if (m_attack_Rand >= 4) {
			ChangeState(Enemy_Boss::enState_Defence);
		}
		//4未満なら尻尾攻撃
		else {
			ChangeState(Enemy_Boss::enState_Attack_Tail);
		}
	}
	//falseなら遠距離パターンに
	else {
		//11以上なら空ブレス
		if (m_attack_Rand >= 11) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		}
		//8以上なら滑空突進
		else if (m_attack_Rand >= 8) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		//2以上ならブレス
		else if (m_attack_Rand >= 2) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//2未満なら近づく
		//パターン段階を1上げる
		else {
			m_pattern++;
			ChangeState(Enemy_Boss::enState_Move);
		}
	}
	////21以上なら滑空突進
	//if (m_attack_Rand >= 21) {

	//}
	////18以上なら空ブレス
	//else if (m_attack_Rand >= 18) {

	//}

}

void BossPattern::DefenseMode()
{
	//m_attack_Rand = this->BossPatternMode();
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//12以上なら噛みつき
		if (m_attack_Rand >= 12) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//9以上なら距離をとる
		//パターン段階を1下げる
		else if (m_attack_Rand >= 9) {
			m_pattern--;
			ChangeState(Enemy_Boss::enState_Takeoff);
		}
		//5以上ならブレス
		else if (m_attack_Rand >= 5) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		////4以上なら尻尾攻撃
		//else if (m_attack_Rand >= 4) {

		//}
		//5未満ならガード
		else {
			ChangeState(Enemy_Boss::enState_Defence);
		}
	}
	//falseなら遠距離パターンに
	else {
		//12以上なら空ブレス
		if (m_attack_Rand >= 12) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		}
		////7以上なら滑空突進
		//else if (m_attack_Rand >= 7) {

		//}
		//3以上ならブレス
		else if (m_attack_Rand >= 3) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//3未満なら近づく
		//パターン段階を1上げる
		else {
			m_pattern++;
			ChangeState(Enemy_Boss::enState_Move);
		}
	}

	////22以上なら滑空突進
	//if (m_attack_Rand >= 22) {
	//}
	////19以上なら空ブレス
	//else if (m_attack_Rand >= 19) {
	//}
	////15以上なら噛みつき
	//else if (m_attack_Rand >= 15) {
	//	//m_isBiting
	//}
	////9以上ならブレス
	//else if (m_attack_Rand >= 9) {
	//	//m_isShoot
	//}
	////4以上ならガード
	//else if (m_attack_Rand >= 4) {
	//	//m_isTail
	//}
	////4未満なら距離をとる
	//else {
}

void BossPattern::NormalMode()
{
	//m_attack_Rand = this->BossPatternMode();
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//11以上なら距離をとる
		//パターン段階を1下げる
		if (m_attack_Rand >= 11) {
			m_pattern--;
			ChangeState(Enemy_Boss::enState_Takeoff);
		}
		//9以上なら噛みつき
		else if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//6以上ならガード
		else if (m_attack_Rand >= 6) {
			ChangeState(Enemy_Boss::enState_Defence);
		}
		//4以上ならブレス
		else if (m_attack_Rand >= 4) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//4未満なら尻尾攻撃
		else {
			ChangeState(Enemy_Boss::enState_Attack_Tail);
		}
	}
	//falseなら遠距離パターンに
	else {
		//12以上なら空ブレス
		if (m_attack_Rand >= 12) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		}
		//9以上なら滑空突進
		else if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		//4以上ならブレス
		else if (m_attack_Rand >= 4) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//4未満なら近づく
		//パターン段階を1上げる
		else {
			m_pattern++;
			ChangeState(Enemy_Boss::enState_Move);
		}
	}
	////23以上なら滑空突進
	//if (m_attack_Rand >= 23) {
	//}
	////19以上なら空ブレス
	//else if (m_attack_Rand >= 19) {
	//}
	////16以上ならガード
	//else if (m_attack_Rand >= 16) {
	//	//m_isBiting
	//}
	////12以上なら噛みつき
	//else if (m_attack_Rand >= 12) {
	//	//m_isShoot
	//}
	////8以上ならブレス
	//else if (m_attack_Rand >= 8) {
	//}
	////4以上なら距離をとる
	//else if (m_attack_Rand >= 4) {
	//	//m_isTail
	//}
	////4未満なら尻尾攻撃
	//else {
	//}

}

void BossPattern::AttackMode()
{
	//m_attack_Rand = this->BossPatternMode();
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//12以上なら距離をとる
		//パターン段階を1下げる
		if (m_attack_Rand >= 12) {
			m_pattern--;
			ChangeState(Enemy_Boss::enState_Takeoff);
		}
		//9以上ならガード
		else if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Defence);
		}
		//6以上なら噛みつき
		else if (m_attack_Rand >= 6) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//4以上ならブレス
		else if (m_attack_Rand >= 4) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//4未満なら尻尾攻撃
		else {
			ChangeState(Enemy_Boss::enState_Attack_Tail);
		}
	}
	//falseなら遠距離パターンに
	else {
		//12以上なら空ブレス
		if (m_attack_Rand >= 12) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		}
		//9以上なら滑空突進
		else if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		//4以上ならブレス
		else if (m_attack_Rand >= 5) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);

		}
		//5未満なら近づく
		//パターン段階を1上げる
		else {
			m_pattern++;
			ChangeState(Enemy_Boss::enState_Move);
		}
	}
	////22以上なら滑空突進
	//if (m_attack_Rand >= 22) {
	//	
	//}
	////18以上ならブレス
	//else if (m_attack_Rand >= 18) {
	//	
	//}
	////13以上なら噛みつき
	//else if (m_attack_Rand >= 13) {
	//	//m_isBiting
	//}
	////9以上ならブレス
	//else if (m_attack_Rand >= 9) {
	//	//m_isShoot
	//}
	////3以上なら尻尾攻撃
	//else if (m_attack_Rand >= 3) {
	//	//m_isTail
	//}
	////3未満なら距離をとる
	//else {
}

void BossPattern::SuperAttackMode()
{
	//m_attack_Rand = this->BossPatternMode();
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//13以上なら距離をとる
		//パターン段階を1下げる
		if (m_attack_Rand >= 13) {
			ChangeState(Enemy_Boss::enState_Takeoff);			m_pattern--;
		}
		//9以上ならガード
		else if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Defence);
		}
		//6以上なら噛みつき
		else if (m_attack_Rand >= 6) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//4以上ならブレス
		else if (m_attack_Rand >= 4) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//4未満なら尻尾攻撃
		else {
			ChangeState(Enemy_Boss::enState_Attack_Tail);
		}
	}
	//falseなら遠距離パターンに
	else {
		//12以上なら空ブレス
		if (m_attack_Rand >= 12) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		}
		//9以上なら滑空突進
		else if (m_attack_Rand >= 8) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		//5以上ならブレス
		else if (m_attack_Rand >= 5) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//5未満なら近づく
		else {
			ChangeState(Enemy_Boss::enState_Move);
		}
	}

	////23以上なら空ブレス
	//if (m_attack_Rand >= 23) {
	//	//m_isFlyShoot
	//}
	////20以上なら滑空突進
	//else if (m_attack_Rand >= 21) {
	//	//m_isFlyAttack
	//}
	////15以上なら噛みつき
	//else if (m_attack_Rand >= 15) {
	//	//m_isBiting
	//}
	////10以上ならブレス
	//else if (m_attack_Rand >= 10){
	//	//m_isShoot
	//}
	////5以上なら尻尾攻撃
	//else if (m_attack_Rand >= 5) {
	//	//m_isTail
	//}
	////5未満なら距離をとる
	//else {
}
