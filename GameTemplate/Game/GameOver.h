#pragma once
#include <SpriteRender.h>

class GameOver :public IGameObject
{
public:
	GameOver() {};
	~GameOver();

	bool Start();
	//�`��֐��B
	void Render(RenderContext& rc);
	//�X�V�����B
	void Update();
private:
	//�X�v���C�g�����_�[�B
	SpriteRender m_spriteRender;

};

