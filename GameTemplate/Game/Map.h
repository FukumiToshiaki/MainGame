#pragma once
class Map : public IGameObject
{
public:
    Map();
    ~Map();

    bool Start();

    void Update();
    //描画関数。

    void Render(RenderContext& rc);


private:
    //モデルレンダ―。        
    Vector3						m_scale = Vector3::One;			//大きさ。
    ModelRender m_modelRender;
    ModelRender m_modelRender_Wall;
    Vector3 m_test_Pos;
    PhysicsStaticObject physicsStaticObject;
    PhysicsStaticObject physicsStaticObject_Wall;
    Vector3 m_pos;  //ポジション
};

