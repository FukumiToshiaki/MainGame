#include "stdafx.h"
#include "Butten_UI.h"
#include "Game.h"

namespace {
    const Vector3 n_buttenY_Pos{ 670.0f,-70.0f,0.0f };
    const Vector3 n_buttenLB_Pos{ 450.0f,-250.0f,0.0f };
    const Vector4 n_buttenY_UI_COLOR = { 0.1f, 0.1f, 0.1f, 1.0f };
}
bool Butten_UI::Start()
{
    m_buttenY_UI.Init("Assets/Sprite/Y.dds", 100.0f, 100.0f);
    m_buttenY_UI.SetPosition(n_buttenY_Pos);
    m_buttenLB_UI.Init("Assets/Sprite/LB.dds", 200.0f, 300.0f);
    m_buttenLB_UI.SetPosition(n_buttenLB_Pos);

    m_game = FindGO<Game>("game");

    return true;
}

void Butten_UI::Update()
{
    m_buttenY_UI.Update();
    m_buttenLB_UI.Update();

}

void Butten_UI::WipeCalc()
{
    int buffersize = sizeof(float);
    

}

void Butten_UI::ColorCalc()
{
}

void Butten_UI::Render(RenderContext& rc)
{

    m_game = FindGO<Game>("game");
    m_buttenLB_UI.Draw(rc);
    m_buttenY_UI.Draw(rc);
}
