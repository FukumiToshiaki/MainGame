#include "stdafx.h"
//#include "Time_Limit_UI.h"
//
//namespace {
//	//HP�̈ʒu
//	const Vector3 n_Time_Position{ -760.0f,-360.0f,0.0f };
//	//HP�̈ʒu
//	const Vector3 n_Time_Position_Red{ -760.0f,-360.0f,0.0f };
//	//B��C�̊�_
//	const Vector2 n_pivot_HP_Damage{ 0,0.5 };
//	//delaytimer�̏����ݒ莞��
//	float m_delaytime = 0.7f;
//}
//
//void Time_Limit_UI::Update()
//{
//	//wchar_t wcsbuf[256];
//	//swprintf_s(wcsbuf, 256, L"%d", int(m_time_Limit));
//
//	////�\������e�L�X�g��ݒ�B
//	//m_fontRender.SetText(wcsbuf);
//	////�t�H���g�̈ʒu��ݒ�B
//	//m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
//	////�t�H���g�̑傫����ݒ�B
//	//m_fontRender.SetScale(3.5f);
//	////�t�H���g�̐F��ݒ�B
//	//m_fontRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });
//
//	m_time_Limit -= g_gameTime->GetFrameDeltaTime();
//
//
//}
//
//void Time_Limit_UI::Test()
//{
//	//�p�x�����W�A���P�ʂɕϊ����܂�
//	float angle = (m_degree * PI) / 180.0f;
//
//}
//
//void Time_Limit_UI::Render(RenderContext& rc)
//{
//	//�t�H���g��`�悷��B
//	m_fontRender.Draw(rc);
//}