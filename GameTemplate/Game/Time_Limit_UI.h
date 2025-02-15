//#pragma once
//#include <FontRender.h>
//#include <SpriteRender.h>
//const float PI = 3.14159f;
//
//#define DecreaseTransitionIN0	m_decrease_TRAN = en_Standby_TRAN;
//#define DecreaseTransitionIN1	m_decrease_TRAN = en_DelayTimeON_TRAN
//#define DecreaseTransitionIN2	m_decrease_TRAN = en_DelayTimeLoop_TRAN;
//#define DecreaseTransitionIN3	m_decrease_TRAN = en_TransparentDecreaseCalc_TRAN;
//#define DecreaseTransitionIN4	m_decrease_TRAN = en_TransparentDecreaseON_TRAN
//#define DecreaseTransition0 m_decrease_TRAN == en_Standby_TRAN
//#define DecreaseTransition1 m_decrease_TRAN == en_DelayTimeON_TRAN
//#define DecreaseTransition2	m_decrease_TRAN == en_DelayTimeLoop_TRAN
//#define DecreaseTransition3	m_decrease_TRAN == en_TransparentDecreaseCalc_TRAN
//#define DecreaseTransition4	m_decrease_TRAN == en_TransparentDecreaseON_TRAN
//
//class Math;
//class Time_Limit_UI : public IGameObject
//{
//public:
//	//透過UI減少還移
//	enum DecreaseTransition {
//		//待機0
//		en_Standby_TRAN,
//		//遅延開始1
//		en_DelayTimeON_TRAN,
//		//遅延処理2
//		en_DelayTimeLoop_TRAN,
//		//透過UI減少計算3
//		en_TransparentDecreaseCalc_TRAN,
//		//透過UI減少開始4
//		en_TransparentDecreaseON_TRAN
//	};
//
//	Time_Limit_UI() {};
//	~Time_Limit_UI() {};
//	//bool Start();
//	void Update();
//	void Test();
//	void Render(RenderContext& renderContext);//モデル
//
//	float GetTime_Limit()
//	{
//		//制限時間
//		return m_time_Limit;
//	}
//private:
//	//////////////////////////////////////
//	// メンバ変数。
//	//////////////////////////////////////
//	FontRender m_fontRender;				//レンダー
//	/////////////////////////////////////////メンバ変数
////HPUI
//	SpriteRender m_hpUI_A;
//	//HPバー
//	SpriteRender m_hpUI_B;
//	//透過HPバー
//	SpriteRender m_hpUI_C;
//	//透過UI減少遷移
//	DecreaseTransition m_decrease_TRAN = en_Standby_TRAN;
//	/////////////////////////////////////////変数
//	//最大HP
//	float m_fullhp = 50;
//	//現在HP　
//	float m_nowhp = m_fullhp;
//	//過去HP
//	float m_oldhp = m_fullhp;
//	//現在hpバースケール(動かすのはm_hpUI_B、zは固定)
//	Vector3 m_scale_B = { 1.0,1.0,1.0 };
//	//現在透過hpバースケール(動かすのはm_hpUI_C、zは固定)
//	Vector3 m_scale_C = { 1.0,1.0,1.0 };
//	//減少遅延タイマー
//	float m_delaytimer = 0.0f;
//	//透過減少割合
//	Vector3 m_changeS_C = m_scale_C;
//	//現在透過減少値
//	Vector3 m_nowScale = m_hpUI_C.GetScale();
//	//プレイヤーの表示のポジション
//	Vector3 m_pos = { 0.0f,0.0f,0.0f };
//	//プレイヤーの表示の最初のポジション
//	Vector3 m_firstPos = { 0.0f,0.0f,0.0f };
//	//スプライトポジション
//	Vector2 m_spritePos = Vector2::Zero;
//	//スプライトレンダー
//	SpriteRender m_spriteRender;
//	//角度
//	float m_degree = 360.0f;   
//	/////////////////////////////////////////初期設定系統
//
//
//	float m_time_Limit = 900.0f;				//制限時間　60秒
//};
//
