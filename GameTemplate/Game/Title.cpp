#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::~Title()
{
}

bool Title::Start()
{
	//タイトルの画像
	m_spriteRender_title.Init("Assets/modelData/test/Test_Start.DDS", 1920.0f, 1080.0f);

	//Sprite表示用のシェーダーのファイルパスを指定する。
	return true;
}

void Title::Render(RenderContext& rc)
{
	//画像を描画する。
	m_spriteRender_title.Draw(rc);			//タイトルの画像
}

void Title::Update()
{
	//Aボタンを押したら
	if (g_pad[0]->IsTrigger(enButtonA)) {
		NewGO<Game>(0, "game");
		//自身を削除する
		DeleteGO(this);
	}
}
