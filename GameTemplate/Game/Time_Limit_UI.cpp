#include "stdafx.h"
#include "Time_Limit_UI.h"

void Time_Limit_UI::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d", int(m_time_Limit));

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(3.5f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	m_time_Limit -= g_gameTime->GetFrameDeltaTime();


}

void Time_Limit_UI::Render(RenderContext& rc)
{
	//フォントを描画する。
	m_fontRender.Draw(rc);
}
