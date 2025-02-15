#include "stdafx.h"
#include "Countdown.h"
#include "Game.h"

Countdown::Countdown()
{
}

bool Countdown::Start()
{
	m_game = FindGO<Game>("game");

	return true;
}

void Countdown::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d", int(m_countDown));
	if (m_countDown < 0) {
		swprintf_s(wcsbuf, 256, L"START");
	}
	if (m_countDown < -1.0f) {
		m_isCountDown = true;
		DeleteGO(this);
	}

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-500.0f, 0.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(15.5f);
	//フォントの色を設定。
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });


	m_countDown -= g_gameTime->GetFrameDeltaTime();;
}

void Countdown::Render(RenderContext& rc)
{
	//フォントを描画する。
	m_fontRender.Draw(rc);
}