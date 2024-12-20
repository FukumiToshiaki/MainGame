#pragma once
#include <SpriteRender.h>

class Title : public IGameObject
{
public:
	Title() {};
	~Title();
	bool Start();
	//描画関数。
	void Render(RenderContext& rc);
	//更新処理。
	void Update();
private:
	//スプライトレンダー。
	SpriteRender m_spriteRender_title;

	
};

