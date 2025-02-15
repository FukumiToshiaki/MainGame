#include "stdafx.h"
//#include "Time_Limit_UI.h"
//
//namespace {
//	//HPの位置
//	const Vector3 n_Time_Position{ -760.0f,-360.0f,0.0f };
//	//HPの位置
//	const Vector3 n_Time_Position_Red{ -760.0f,-360.0f,0.0f };
//	//BとCの基点
//	const Vector2 n_pivot_HP_Damage{ 0,0.5 };
//	//delaytimerの初期設定時間
//	float m_delaytime = 0.7f;
//}
//
//void Time_Limit_UI::Update()
//{
//	//wchar_t wcsbuf[256];
//	//swprintf_s(wcsbuf, 256, L"%d", int(m_time_Limit));
//
//	////表示するテキストを設定。
//	//m_fontRender.SetText(wcsbuf);
//	////フォントの位置を設定。
//	//m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
//	////フォントの大きさを設定。
//	//m_fontRender.SetScale(3.5f);
//	////フォントの色を設定。
//	//m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });
//
//	m_time_Limit -= g_gameTime->GetFrameDeltaTime();
//
//
//}
//
//void Time_Limit_UI::Test()
//{
//	//角度をラジアン単位に変換します
//	float angle = (m_degree * PI) / 180.0f;
//
//}
//
//void Time_Limit_UI::Render(RenderContext& rc)
//{
//	//フォントを描画する。
//	m_fontRender.Draw(rc);
//}