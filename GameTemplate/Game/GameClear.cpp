#include "stdafx.h"
#include "GameClear.h"
#include "Title.h"

GameClear::~GameClear()
{

}

bool GameClear::Start()
{
	//タイトルの画像
	m_spriteRender.Init("Assets/modelData/test/Test_Clear.dds", 1920.0f, 1080.0f);

	return true;
}

void GameClear::Update()
{	
	//Aボタンを押したら
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Title>(0, "title");
		//自身を削除する
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	//画像を描画する。
	m_spriteRender.Draw(rc);			//タイトルの画像
}