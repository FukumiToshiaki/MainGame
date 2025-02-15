#pragma once
#include <SpriteRender.h>
#define DecreaseTransitionIN0	m_decrease_TRAN = en_Standby_TRAN;
#define DecreaseTransitionIN1	m_decrease_TRAN = en_DelayTimeON_TRAN
#define DecreaseTransitionIN2	m_decrease_TRAN = en_DelayTimeLoop_TRAN;
#define DecreaseTransitionIN3	m_decrease_TRAN = en_TransparentDecreaseCalc_TRAN;
#define DecreaseTransitionIN4	m_decrease_TRAN = en_TransparentDecreaseON_TRAN
#define DecreaseTransition0 m_decrease_TRAN == en_Standby_TRAN
#define DecreaseTransition1 m_decrease_TRAN == en_DelayTimeON_TRAN
#define DecreaseTransition2	m_decrease_TRAN == en_DelayTimeLoop_TRAN
#define DecreaseTransition3	m_decrease_TRAN == en_TransparentDecreaseCalc_TRAN
#define DecreaseTransition4	m_decrease_TRAN == en_TransparentDecreaseON_TRAN
class Game;
class Enemy_Boss;
class Boss_HP_UI :public IGameObject
{
public:
	//透過UI減少還移
	enum DecreaseTransition {
		//待機0
		en_Standby_TRAN,
		//遅延開始1
		en_DelayTimeON_TRAN,
		//遅延処理2
		en_DelayTimeLoop_TRAN,
		//透過UI減少計算3
		en_TransparentDecreaseCalc_TRAN,
		//透過UI減少開始4
		en_TransparentDecreaseON_TRAN
	};
	////////////////////////////////////////
	//関数
	Boss_HP_UI() {}
	~Boss_HP_UI() {}
	//スタート関数
	bool Start();
	//アップデート
	void Update();
	//加減計算
	void Adjustment();
	//透過バー加減計算
	void AdjustmentTransparent();
	//モデル
	void Render(RenderContext& renderContext);
	//キャラの表示
	void Model1P();
	//HP減少処理
	void DecreaseHP(float decrease)
	{
		//HPを減少値減らす
		m_nowhp -= decrease;
		return;
	}

	float GetNowHP()
	{
		return m_nowhp;
	}

private:
	/////////////////////////////////////////メンバ変数
	//HPUI
	SpriteRender m_hpUI_A;
	//HPバー
	SpriteRender m_hpUI_B;
	//透過HPバー
	SpriteRender m_hpUI_C;
	//透過UI減少遷移
	DecreaseTransition m_decrease_TRAN = en_Standby_TRAN;
	//ゲーム
	Game* m_game = nullptr;
	//プレイヤーベース
	Enemy_Boss* m_enemy_boss = nullptr;
	/////////////////////////////////////////変数
	//最大HP
	float m_fullhp = 100.0f;
	//現在HP　
	float m_nowhp = m_fullhp;
	//過去HP
	float m_oldhp = m_fullhp;
	//現在hpバースケール(動かすのはm_hpUI_B、zは固定)
	Vector3 m_scale_B = { 0.8f,0.8f,1.0f };
	//現在透過hpバースケール(動かすのはm_hpUI_C、zは固定)
	Vector3 m_scale_C = { 0.8f,0.8f,1.0f };
	//減少遅延タイマー
	float m_delaytimer = 0.0f;
	//透過減少割合
	Vector3 m_changeS_C = m_scale_C;
	//現在透過減少値
	Vector3 m_nowScale = m_hpUI_C.GetScale();
	//ボスの表示のポジション
	Vector3 m_pos = { 0.0f,0.0f,0.0f };
	//ボスの表示の最初のポジション
	Vector3 m_firstPos = { 0.0f,0.0f,0.0f };
	//スプライトポジション
	Vector2 m_spritePos = Vector2::Zero;
	//スプライトレンダー
	SpriteRender m_spriteRender;

	Quaternion m_quaternion = { 0.0f,0.0f,0.0f,0.0f };
	/////////////////////////////////////////初期設定系統
};
