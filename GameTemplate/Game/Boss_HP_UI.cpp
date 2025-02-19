#include "stdafx.h"
#include "Boss_HP_UI.h"
#include "Game.h"
#include "Enemy_Boss.h"

namespace {
	//HPの位置
	const Vector3 n_position_HP{ 110.0f,410.0f,0.0f };
	//HPの位置
	const Vector3 n_position_Damage{ 110.0f,410.0f,0.0f };
	//BとCの基点
	const Vector2 n_pivot_HP_Damage{ 0,0.5 };
	//スケール
	const Vector3 n_scale{ 0.8f,0.7f,0.7f };
	//delaytimerの初期設定時間
	float m_delaytime = 0.7f;
}

bool Boss_HP_UI::Start()
{
	m_game = FindGO<Game>("game");
	m_enemy_boss = FindGO<Enemy_Boss>("enemy_boss");//場所を教える
	//画像設定
	m_hpUI_A.Init("Assets/Sprite/Boss_HP_RED.DDS", 900.0f, 600.0f);
	//画像設定
	m_hpUI_B.Init("Assets/Sprite/Boss_HP.DDS", 900.0f, 600.0f);
	//位置設定
	m_hpUI_A.SetPosition(n_position_HP);
	//位置設定
	m_hpUI_B.SetPosition(n_position_Damage);
	//基点設定
	m_hpUI_A.SetPivot(n_pivot_HP_Damage);
	m_hpUI_B.SetPivot(n_pivot_HP_Damage);
	//スケール
	m_hpUI_A.SetScale(n_scale);
	m_hpUI_B.SetScale(n_scale);
	m_firstPos = m_pos;
	return true;
}

void Boss_HP_UI::Update()
{
	//減算計算処理
	Adjustment();
	//透過減算計算処理
	AdjustmentTransparent();
	//描画処理
	m_hpUI_A.Update();
	m_hpUI_B.Update();
}

void Boss_HP_UI::Adjustment()
{
	//0以下にしない
	if (m_nowhp < 0) {
		m_nowhp = 0;
	}
	//現在HPが減少したら
	if (m_nowhp < m_oldhp)
	{
		float a = m_nowhp;
		float b = m_fullhp;
		//現在HPと最大HPの割合を計算
		float ratio = a / b;
		//現在のm_hpUI_Bのscale.xと割合を計算
		Vector3 changeS_B = m_scale_B;
		changeS_B.x = m_scale_B.x * ratio;
		m_hpUI_B.SetScale(changeS_B);
		//過去HPに現在のHPを保存
		m_oldhp = m_nowhp;
		//透過遅延開始
		DecreaseTransitionIN1;
	}
}

void Boss_HP_UI::AdjustmentTransparent()
{
	if (DecreaseTransition0) {
		return;
	}
	if (DecreaseTransition3 || DecreaseTransition4)
	{
		if (DecreaseTransition3)
		{
			float a = m_nowhp;
			float b = m_fullhp;
			//現在HPと最大HPの割合を計算
			float ratio = a / b;
			//現在のm_hpUI_Bのscale.xと割合を計算
			m_changeS_C.x = m_scale_C.x * ratio;
			//減少処理に移行
			DecreaseTransitionIN4;
		}
		//減少処理、繰り返し処理で計算した割合と現在のScale.xと同値になるまで減算
		if (DecreaseTransition4)
		{
			//めちゃくちゃ細かく減らす
			m_nowScale.x -= 0.009f;
			//0以下だったら0に戻す
			if (m_nowScale.x < 0)
			{
				m_nowScale.x = 0;
			}
			//大きさを変更する
			m_hpUI_C.SetScale(m_nowScale);

			//現在scaleが変更後scale以下になったら
			if (m_changeS_C.x > m_nowScale.x)
			{
				//念のため初期化
				m_changeS_C = m_scale_C;
				m_nowScale = m_hpUI_C.GetScale();
				//スタンバイに移行
				DecreaseTransitionIN0;
				return;
			}
			//変更後以上の場合
			else
				return;
		}
	}
	//ここから下の処理は減少遅延のタイマー処理

	//delaytimer減少処理
	if (0.0 < m_delaytimer && DecreaseTransition2)
	{
		m_delaytimer -= g_gameTime->GetFrameDeltaTime();
	}
	//delaytimerが0になったら
	else if (m_delaytimer < 0.0 && DecreaseTransition2)
	{
		//透過UI減算割合計算処理に移行
		DecreaseTransitionIN3;
		return;
	}

	//m_delayloopがtrueの時はここから後は処理しない
	if (DecreaseTransition2)
		return;

	//透過減少遅延タイマー初期化
	m_delaytimer = m_delaytime;
	//遅延処理に移行
	DecreaseTransitionIN2;
}

void Boss_HP_UI::Render(RenderContext& rc)
{
	m_game = FindGO<Game>("game");
	//HPUIの描画処理を先に
	m_hpUI_A.Draw(rc);
	//バーの描画処理を後に
	m_hpUI_B.Draw(rc);
}