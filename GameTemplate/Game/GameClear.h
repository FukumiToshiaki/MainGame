#pragma once
#include <SpriteRender.h>

class GameClear :public IGameObject
{
public:
	GameClear() {};
	~GameClear();

	bool Start();
	//�`��֐��B
	void Render(RenderContext& rc);
	//�X�V�����B
	void Update();
private:
	//�X�v���C�g�����_�[�B
	SpriteRender m_spriteRender;

};