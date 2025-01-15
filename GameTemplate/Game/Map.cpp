#include "stdafx.h"
#include "Map.h"
#define SCALE 5.1f

bool Map::Start()
{
    const Vector3 m_scale = { SCALE,SCALE,SCALE }; //大きさ
    m_modelRender.SetScale(m_scale);

    m_modelRender.Init("Assets/modelData/GameMap/Map.tkm", nullptr, 0, enModelUpAxisZ, false, true);
    m_modelRender.SetShadowChasterFlag(false);
    m_modelRender.SetPosition(m_pos);
    //モデルを更新する。
    m_modelRender.Update();

    const Vector3 m_scaleWall = { SCALE,SCALE,SCALE }; //大きさ
    m_modelRender_Wall.SetScale(m_scaleWall);

    m_modelRender_Wall.Init("Assets/modelData/GameMap/MapWall.tkm", nullptr, 0, enModelUpAxisZ, false, true);
    m_modelRender_Wall.SetShadowChasterFlag(false);
    m_modelRender_Wall.SetPosition(m_pos);
    //モデルを更新する。
    m_modelRender_Wall.Update();


    physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
    m_modelRender.GetModel().GetWorldMatrix());
    physicsStaticObject_Wall.CreateFromModel(m_modelRender_Wall.GetModel(),
    m_modelRender_Wall.GetModel().GetWorldMatrix());
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

    m_modelRender_Wall.SetPosition(m_pos);
    m_modelRender_Wall.Update();
}

void Map::Render(RenderContext& rc)
{
    //m_modelRender_Wall.Draw(rc);

    m_modelRender.Draw(rc);
}