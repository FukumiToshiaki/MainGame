#pragma once
#include <SpriteRender.h>

class Title : public IGameObject
{
public:
	Title() {};
	~Title();
	bool Start();
	//�`��֐��B
	void Render(RenderContext& rc);
	//�X�V�����B
	void Update();
private:
	//�X�v���C�g�����_�[�B
	SpriteRender m_spriteRender_title;

	
};

