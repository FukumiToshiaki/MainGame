#include "stdafx.h"
#include "BossAI.h"
#include "Enemy_Boss.h"
#include "Player.h"
#include "Boss_Shoot.h"

#include "math.h"
#include <numeric>

using namespace std;

unordered_map<string, vector<double>> Q_table;
#define PLAYERLASTHP 20.0f
#define BOSSLASTHP 20.0f
#define EPSILON 0.2f

//状態を文字列に変換
string get_state(int player_distance, int enemy_hp, int player_action, int last_action) {
	return to_string(player_distance) + "_" + to_string(enemy_hp) + "_" +
		to_string(player_action) + "_" + to_string(last_action);
}

//ε-greedy法で行動を選択
int choose_action(const string& state) {
	if ((rand() % 100) / 100.0 < EPSILON || Q_table[state].empty()) {
		return rand() % 5;  // 0～4のランダム行動
	}
	return max_element(Q_table[state].begin(), Q_table[state].end()) - Q_table[state].begin();
}

BossAI::~BossAI()
{
}

bool BossAI::Start()
{
	Enemy_Boss::Start();
	m_boss_Shoot = FindGO<Boss_Shoot>("boss_shoot");
	m_player = FindGO<Player>("player");
	return true;
}

void BossAI::Update()
{

}

void BossAI::CoolTime()
{
	//Idle状態なら
	if (m_state == enState_Idle) {
		//trueに
		m_iscoolTimeStart = true;
		//ブレスの判定初期化
		//m_isShoot = false;
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

void BossAI::BossTable(const string&state)
{
	if (Q_table.find(state) == Q_table.end()) {
		Q_table[state] = vector<double>(5, 0.0);
	}
}

void BossAI::BossValue(const string& state, int action, double reward, const string& next_state)
{
	BossTable(state);
	BossTable(next_state);

	double max_next_q = *max_element(Q_table[next_state].begin(), Q_table[next_state].end());
	Q_table[state][action] = (1 - 0.1) * Q_table[state][action] + 0.1 * (reward + 0.9 * max_next_q);
}
