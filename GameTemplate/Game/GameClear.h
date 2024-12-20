#pragma once
#include <SpriteRender.h>

class GameClear :public IGameObject
{
public:
	GameClear() {};
	~GameClear();

	bool Start();
	//描画関数。
	void Render(RenderContext& rc);
	//更新処理。
	void Update();
private:
	//スプライトレンダー。
	SpriteRender m_spriteRender;

};