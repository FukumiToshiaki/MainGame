#pragma once
#include "FontRender.h"
class Game;
class Countdown :public IGameObject
{
public:
	Countdown() ;
	~Countdown() {};
	bool Start();
	void Update();
	void Render(RenderContext& renderContext);//���f��

	bool GetIsCountDown()
	{
		return m_isCountDown;
	}

private:
	//////////////////////////////////////
// �����o�ϐ��B
//////////////////////////////////////
	FontRender m_fontRender;
	float m_countDown = 5.0f;				//�X�^�[�g���ԁ@5�b
	Game* m_game = nullptr;//�Q�[��
	bool m_isCountDown = false;				//�J�E���g�_�E���̏�������
};