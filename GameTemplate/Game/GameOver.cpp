#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
GameOver::~GameOver()
{
}

bool GameOver::Start()
{
	//�^�C�g���̉摜
	m_spriteRender.Init("Assets/modelData/test/Test_Over.dds", 1920.0f, 1080.0f);

	return true;
}

void GameOver::Update()
{	
	//A�{�^������������
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "title");

		//���g���폜����
		DeleteGO(this);
	}

}

void GameOver::Render(RenderContext& rc)
{
	//�摜��`�悷��B
	m_spriteRender.Draw(rc);			//�^�C�g���̉摜
}
