#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"

GameClear::~GameClear()
{

}

bool GameClear::Start()
{
	//�^�C�g���̉摜
	m_spriteRender.Init("Assets/modelData/test/Test_Clear.dds", 1920.0f, 1080.0f);

	return true;
}

void GameClear::Update()
{	
	//A�{�^������������
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "title");
		//���g���폜����
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	//�摜��`�悷��B
	m_spriteRender.Draw(rc);			//�^�C�g���̉摜
}