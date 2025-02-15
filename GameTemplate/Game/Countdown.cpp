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

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-500.0f, 0.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(15.5f);
	//�t�H���g�̐F��ݒ�B
	m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });


	m_countDown -= g_gameTime->GetFrameDeltaTime();;
}

void Countdown::Render(RenderContext& rc)
{
	//�t�H���g��`�悷��B
	m_fontRender.Draw(rc);
}