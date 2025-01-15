#pragma once
#include <FontRender.h>
class Time_Limit_UI : public IGameObject
{
public:
	Time_Limit_UI() {};
	~Time_Limit_UI() {};
	//bool Start();
	void Update();
	void Render(RenderContext& renderContext);//モデル

	float GetTime_Limit()
	{
		//制限時間
		return m_time_Limit;
	}
private:
	//////////////////////////////////////
	// メンバ変数。
	//////////////////////////////////////
	FontRender m_fontRender;				//レンダー

	float m_time_Limit = 900.0f;				//制限時間　60秒
};

