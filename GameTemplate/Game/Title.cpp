#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::~Title()
{
}

bool Title::Start()
{
	//�^�C�g���̉摜
	m_spriteRender_title.Init("Assets/modelData/UI/gameclear.dds", 400.0f, 400.0f);

	//m_spriteRender_title.SetMulColor({1.0f,1.0f,1.0f,0.5f});

	m_spriteRender_title.Update();
	//Sprite�\���p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
	return true;
}

void Title::Render(RenderContext& rc)
{
	//�摜��`�悷��B
	m_spriteRender_title.Draw(rc);			//�^�C�g���̉摜
}

void Title::Update()
{
	//�摜�̍X�V�B
	m_spriteRender_title.Update();
	//A�{�^������������
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Game>(0, "game");
		//���g���폜����
		DeleteGO(this);
	}
}
