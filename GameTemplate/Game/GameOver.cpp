#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
GameOver::~GameOver()
{
}

bool GameOver::Start()
{
	//タイトルの画像
	m_spriteRender.Init("Assets/modelData/test/Test_Over.dds", 1920.0f, 1080.0f);

	return true;
}

void GameOver::Update()
{	
	//Aボタンを押したら
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "title");

		//自身を削除する
		DeleteGO(this);
	}

}

void GameOver::Render(RenderContext& rc)
{
	//画像を描画する。
	m_spriteRender.Draw(rc);			//タイトルの画像
}
