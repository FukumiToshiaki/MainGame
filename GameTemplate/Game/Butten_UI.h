#pragma once
#include <SpriteRender.h>
const float PI = 3.14159f;

class Game;
class Butten_UI :public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Butten_UI() {};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Butten_UI() {};

	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// ワイプ計算
	/// </summary>
	void WipeCalc();
	/// <summary>
	/// UIカラー計算
	/// </summary>
	void ColorCalc();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Render(RenderContext& rc);

	/// <summary>
	/// Yボタンのboolの変更
	/// </summary>
	void SetisYPush(bool YPush)
	{
		m_isYPush = YPush;
	}
private:
	/// <summary>
	/// フォントカラー変更に使用するBool
	/// </summary>
	bool m_isFontColor = false;
	/// <summary>
	/// Yボタンの表示スプライト
	/// </summary>
	SpriteRender m_buttenY_UI;
	/// <summary>
	/// Xボタンの表示スプライト
	/// </summary>
	SpriteRender m_buttenX_UI;
	/// <summary>
	/// Aボタンの表示スプライト
	/// </summary>
	SpriteRender m_buttenA_UI;
	/// <summary>
	/// Bボタンの表示スプライト
	/// </summary>
	SpriteRender m_buttenB_UI;
	/// <summary>
	/// RTボタンの表示スプライト
	/// </summary>
	SpriteRender m_buttenRT_UI;
	/// <summary>
	/// RBボタンの表示スプライト
	/// </summary>
	SpriteRender m_buttenRB_UI;
	/// <summary>
	/// LBボタンの表示スプライト
	/// </summary>
	SpriteRender m_buttenLB_UI;
	/// <summary>
	/// ゲームのインスタンスを格納するポインタ変数
	/// </summary>
	Game* m_game = nullptr;
	/// <summary>
	/// Yボタンが押されているかどうか
	/// </summary>
	bool m_isYPush = false;

	DirectX::SpriteBatch* m_spriteBatch;  //SpriteBatch
	/// <summary>
	/// 角度
	/// </summary>
	float m_degree = 360.0f;   
};

