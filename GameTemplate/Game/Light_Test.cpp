#include "stdafx.h"
#include "Light_Test.h"

bool Light_Test::Start()
{

	m_pointLightList.Init();
	Vector3 pointLightPosition = { 0.0f, 2000.0f, 10.0f };
	//ポイントライトの座標を設定する。
	m_pointLightList.SetPosition(pointLightPosition);
		//ポイントライトのパラメータを設定する。
	//ポイントライトの色。
	m_pointLightList.SetColor(Vector3(1.0f, 9.0f, 1.0f));
	//ポイントライトの影響範囲。
	m_pointLightList.SetRange(3000.0f);
	//ポイントライトの減衰率。
	m_pointLightList.SetAffectPowParam(1.5f);
	////trueにすると、レベルの方でモデルが読み込まれない。
	return true;

}
void Light_Test::Update()
{

}

void Light_Test::Render(RenderContext& rc)
{
}
