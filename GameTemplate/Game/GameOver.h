#pragma once
#include <SpriteRender.h>

class GameOver :public IGameObject
{
public:
	GameOver() {};
	~GameOver();

	bool Start();
	//描画関数。
	void Render(RenderContext& rc);
	//更新処理。
	void Update();
private:
	//スプライトレンダー。
	SpriteRender m_spriteRender;

};

