#pragma once
#include "FontRender.h"
class Game;
class Countdown :public IGameObject
{
public:
	Countdown() ;
	~Countdown() {};
	bool Start();
	void Update();
	void Render(RenderContext& renderContext);//モデル

	bool GetIsCountDown()
	{
		return m_isCountDown;
	}

private:
	//////////////////////////////////////
// メンバ変数。
//////////////////////////////////////
	FontRender m_fontRender;
	float m_countDown = 5.0f;				//スタート時間　5秒
	Game* m_game = nullptr;//ゲーム
	bool m_isCountDown = false;				//カウントダウンの消去判定
};