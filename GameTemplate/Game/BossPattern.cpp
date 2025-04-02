#include "stdafx.h"
#include "BossPattern.h"
#include "Enemy_Boss.h"
#include "Player.h"
#include "Boss_Shoot.h"

#include "math.h"
#include <numeric>

#define DISTANCE_POS 12000.0f
#define FIRST_PHASE 80.0f
#define SECOND_PHASE 65.0f
#define FINAL_PHASE 50.0f
#define MELEE_DISTANCE 1500.0f
#define CHASE_SPEED 700.0f
#define FLY_SPEED 200.0f
#define PLAYERLASTHP 20.0f
#define BOSSLASTHP 20.0f
#define LASTCOOLTIME 2

BossPattern::~BossPattern()
{
	
}

bool BossPattern::Start()
{
	Enemy_Boss::Start();
	m_boss_Shoot = FindGO<Boss_Shoot>("boss_shoot");
	m_player = FindGO<Player>("player");
	return true;
}

void BossPattern::Update()
{
	//クールタイム関数
	CoolTime();
	//ボスの行動するための数値の関数
	BossPatternMode();
	//近距離か遠距離か
	DistancePattern();
	//基底クラスのUpdateを呼ぶ
	Enemy_Boss::Update();

	//フラグが立っていないなら計算する必要がないので、早期リターン
	if (!m_isUnderPattern) {
		return;
	}
	if (m_state != enState_Landing) {
		//効果音のフラグをtrue
		m_isSound = true;
	}
	//咆哮を放つため
	Scream(40,400.0f);
	//他の行動をさせないため
	if (m_state == enState_Attack_Scream) {
		//行動数値を0に戻す
		m_attack_Rand = 0;
		//フラグをfalseに
		m_isUnderPattern = false;
		//クールタイムをランダムに
		m_coolTime = 3.0f;
		//必殺技カウンターを0に戻す
		m_screamCount = 0;
		//効果音のフラグをtrue
		m_isSound = true;
		//これ以上したにいかないために
		return;
	}
	//必殺技のための移動
	//その時は必殺技優先
	if (m_testHP <= FINAL_PHASE && !m_isScream) {
		return;
	}
	//必殺技カウントの増加
	m_screamCount++;
	//プレイヤーのHPが一定数以下の時
	//最後の攻撃モードに移行
	if (m_player->GetHP() < PLAYERLASTHP) {
		AttackModeLast();
		//行動数値を0に戻す
		m_attack_Rand = 0;
		//フラグをfalseに
		m_isUnderPattern = false;
		//クールタイムをランダムに
		m_coolTime = rand() % LASTCOOLTIME;
		//リターン
		return;
	}
	//自分ののHPが一定数以下の時
	//最後の防御モードに移行
	else if (m_testHP < BOSSLASTHP) {
		DefenseModeLast();
		//行動数値を0に戻す
		m_attack_Rand = 0;
		//フラグをfalseに
		m_isUnderPattern = false;
		//クールタイムをランダムに
		m_coolTime = rand() % LASTCOOLTIME;
		//リターン
		return;
	}
	//パタ―ン数値によって変わる
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
	//行動数値を0に戻す
	m_attack_Rand = 0;
	//フラグをfalseに
	m_isUnderPattern = false;
	//クールタイムをランダムに
	m_coolTime = rand() % 4;
}
void BossPattern::CoolTime()
{
	//Idle状態なら
	if (m_state == enState_Idle) {
		//trueに
		m_iscoolTimeStart = true;
		//ブレスの判定初期化
		m_effectCount = 0;
		m_isFlyKeepDistance = false;
		m_boss_Shoot->SetisShoot(false);
	}

	//0秒になっているなら計算する必要ない
	if (m_isUnderPattern) {
		return;
	}
	//trueならクールタイマー開始
	if (m_iscoolTimeStart) {
		m_coolTime -= g_gameTime->GetFrameDeltaTime();
	}
	//プレイヤーかボスの体力が一定数以下なら
	//発狂モード
	if (m_player->GetHP() < PLAYERLASTHP || m_testHP < BOSSLASTHP) {
		if (m_coolTime <= 0.0f && m_state == enState_Idle) {
			m_isUnderPattern = true;
			m_iscoolTimeStart = false;
		}
		//一定数以下なのでreturnする
		return;
	}
	//ここから下は通常モード

	//0秒になったらフラグを立てる
	if (m_coolTime <= 0.0f && m_state == enState_Idle) {
		m_isUnderPattern = true;
		m_iscoolTimeStart = false;
	}
}
void BossPattern::DistancePattern()
{
	if (m_testHP <= FINAL_PHASE && !m_isScream) {
		return;
	}
	//プレイヤーの追跡の変数
	m_distance = m_player->Get_PlayerPos() - m_pos;
	m_distance.y = 0.0f;
	m_diff = m_distance;
	m_diff.Normalize();
	//距離が一定数以下で
	//Move状態なら追いかける
	if (m_distance.Length() <= DISTANCE_POS && m_state == enState_Move) {
		m_moveSpeed = m_diff * CHASE_SPEED;
	}
}
void BossPattern::BossPatternMode()
{
	if (m_testHP <= FINAL_PHASE && !m_isScream) {
		return;
	}
	if (m_isUnderPattern) {
		//距離内なら近距離型のtrueに
		if (m_distance.Length() <= MELEE_DISTANCE) {
			m_isBifurcation = true;
		}
		//違うなら遠距離型のfalseに
		else {
			m_isBifurcation = false;
		}
		//自分のHPが低いほど
		//足す数字を大きくする
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
	}
}
void BossPattern::AttackModeLast()
{
		//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//14以上なら必殺技の咆哮
		if (m_attack_Rand >= 14) {
			ChangeState(Enemy_Boss::enState_Attack_Scream);
		}
		//12以上なら距離をとる
		else if (m_attack_Rand >= 12) {
			ChangeState(Enemy_Boss::enState_Takeoff);
		}
		//9以上ならガード
		else if (m_attack_Rand >= 9) {
			ChangeState(Enemy_Boss::enState_Defence);
		}
		//5以上なら噛みつき
		else if (m_attack_Rand >= 5) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//3以上ならブレス
		else if (m_attack_Rand >= 3) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//3未満なら尻尾攻撃
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
		else {
			ChangeState(Enemy_Boss::enState_Move);
		}
	}
}
void BossPattern::DefenseModeLast()
{
		//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//14以上なら必殺技の咆哮
		if (m_attack_Rand >= 14) {
			ChangeState(Enemy_Boss::enState_Attack_Scream);
		}
		//11以上なら距離をとる
		else if (m_attack_Rand >= 11) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Fly);
		}
		//8以上なら嚙みつき
		else if (m_attack_Rand >= 8) {
			ChangeState(Enemy_Boss::enState_Attack_Biting);
		}
		//6以上ならブレス
		else if (m_attack_Rand >= 6) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//3以上ならガード
		else if (m_attack_Rand >= 3) {
			ChangeState(Enemy_Boss::enState_Defence);
		}
		//3未満なら尻尾攻撃
		else {
			ChangeState(Enemy_Boss::enState_Attack_Tail);
		}
	}
	//falseなら遠距離パターンに
	else {
		//9以上なら空ブレス
		if (m_attack_Rand >=9) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_FlyShoot);
		}
		//6以上なら滑空突進
		else if (m_attack_Rand >= 6) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		//2以上ならブレス
		else if (m_attack_Rand >= 2) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//2未満なら近づく
		else {
			ChangeState(Enemy_Boss::enState_Move);
		}
	}
}
void BossPattern::Scream(int screamcount,float screamdistance)
{	
	//ボスと原点の距離を求める
	Vector3 diff;
	diff = m_screamPos- m_pos;
	Vector3 scream_Arrangement;
	scream_Arrangement = diff;
	diff.Normalize();


	//必殺技
	if (m_testHP <= FINAL_PHASE && !m_isScream) {
		//中央付近にいるなら
		if (scream_Arrangement.Length() <= screamdistance) {
			if (m_isFly_Set) {
				//HPが半分の時に一回
				ChangeState(Enemy_Boss::enState_Landing);
			}
			else {
				m_isScream_Normal = true;
			}
		}
		else {
			if(!m_isFly_Set){
				ChangeState(Enemy_Boss::enState_Takeoff);
				m_isFly_Set = true;
			}
			else {
				ChangeState(Enemy_Boss::enState_Fly);
			}
			if (m_isUnderFly) {
				m_moveSpeed = diff * FLY_SPEED;
			}
		}
	}
	//一定数行動したら
	else if (m_screamCount >= screamcount) {
		//中央付近にいるなら
		if (scream_Arrangement.Length() <= screamdistance) {
			//HPが半分の時に一回
			ChangeState(Enemy_Boss::enState_Landing);
		}
		else {
			if (!m_isFly_Set) {
				ChangeState(Enemy_Boss::enState_Takeoff);
				m_isFly_Set = true;
			}
			else {
				ChangeState(Enemy_Boss::enState_Fly);
			}
			if (m_isUnderFly) {
				m_moveSpeed = diff * FLY_SPEED;
			}
		}
	}
	//ランダムの行動数値がマックスなら
	else if (m_attack_Rand >= 14) {
		//中央付近にいるなら
		if (scream_Arrangement.Length() <= screamdistance) {
			//HPが半分の時に一回
			ChangeState(Enemy_Boss::enState_Landing);
		}
		else {
			if (!m_isFly_Set) {
				ChangeState(Enemy_Boss::enState_Takeoff);
				m_isFly_Set = true;
			}
			else {
				ChangeState(Enemy_Boss::enState_Fly);
			}
			if (m_isUnderFly) {
				m_moveSpeed = diff * FLY_SPEED;
			}
		}
	}
	//咆哮準備が整ったら咆哮
	if (m_isScream_Normal) {
		ChangeState(Enemy_Boss::enState_Attack_Scream);
		//リセット
		m_isScream_Normal = false;
		m_isFly_Set = false;
	}
}
void BossPattern::SuperDefenseMode()
{
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//11以上なら距離をとる
		if (m_attack_Rand >= 11) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Fly);
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
		//7以上なら滑空突進
		else if (m_attack_Rand >= 7) {
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
}
void BossPattern::DefenseMode()
{
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
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Fly);
		}
		//7以上ならブレス
		else if (m_attack_Rand >= 7) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//5以上なら尻尾攻撃
		else if (m_attack_Rand >= 5) {
			ChangeState(Enemy_Boss::enState_Attack_Tail);
		}
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
}
void BossPattern::NormalMode()
{
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//11以上なら距離をとる
		//パターン段階を1下げる
		if (m_attack_Rand >= 11) {
			m_pattern--;
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Fly);
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
}
void BossPattern::AttackMode()
{
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//12以上なら距離をとる
		//パターン段階を1下げる
		if (m_attack_Rand >= 12) {
			m_pattern--;
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Fly);
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
}
void BossPattern::SuperAttackMode()
{
	//trueなら近距離用のパターン
	if (m_isBifurcation) {
		//13以上なら距離をとる
		//パターン段階を1下げる
		if (m_attack_Rand >= 12) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Fly);
			m_pattern--;
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
		//7以上なら滑空突進
		else if (m_attack_Rand >= 7) {
			ChangeState(Enemy_Boss::enState_Takeoff, Enemy_Boss::enState_Attack_Fly);
		}
		//4以上ならブレス
		else if (m_attack_Rand >= 4) {
			ChangeState(Enemy_Boss::enState_Attack_Shoot);
		}
		//4未満なら近づく
		else {
			ChangeState(Enemy_Boss::enState_Move);
		}
	}
}
