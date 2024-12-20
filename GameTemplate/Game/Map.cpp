#include "stdafx.h"
#include "Map.h"
#define SCALE 5.5f

bool Map::Start()
{
    const Vector3 m_scale = { SCALE,SCALE,SCALE }; //大きさ
    m_modelRender.SetScale(m_scale);

    m_modelRender.Init("Assets/modelData/GameMap/Map.tkm", nullptr, 0, enModelUpAxisZ, false, true);
    m_modelRender.SetShadowChasterFlag(false);
    m_modelRender.SetPosition(m_pos);
    //モデルを更新する。
    m_modelRender.Update();

    physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
    m_modelRender.GetModel().GetWorldMatrix());
    
    return true;
}

Map::Map()
{
    //m_test_Pos.y =.0f;
    m_pos.y = 0.0f;
}

Map::~Map()
{

}

void Map::Update()
{
    m_modelRender.SetPosition(m_pos);
    m_modelRender.Update();

    //m_modelRender_Test.SetPosition(m_test_Pos);
   // m_modelRender_Test.Update();
}

void Map::Render(RenderContext& rc)
{
    //m_modelRender_Test.Draw(rc);

     m_modelRender.Draw(rc);
}