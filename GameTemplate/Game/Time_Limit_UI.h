#pragma once
#include <FontRender.h>
class Time_Limit_UI : public IGameObject
{
public:
	Time_Limit_UI() {};
	~Time_Limit_UI() {};
	//bool Start();
	void Update();
	void Render(RenderContext& renderContext);//���f��

	float GetTime_Limit()
	{
		//��������
		return m_time_Limit;
	}
private:
	//////////////////////////////////////
	// �����o�ϐ��B
	//////////////////////////////////////
	FontRender m_fontRender;				//�����_�[

	float m_time_Limit = 900.0f;				//�������ԁ@60�b
};

