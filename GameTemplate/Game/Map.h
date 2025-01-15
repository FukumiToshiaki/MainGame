#pragma once
class Map : public IGameObject
{
public:
    Map();
    ~Map();

    bool Start();

    void Update();
    //�`��֐��B

    void Render(RenderContext& rc);


private:
    //���f�������_�\�B        
    Vector3						m_scale = Vector3::One;			//�傫���B
    ModelRender m_modelRender;
    ModelRender m_modelRender_Wall;
    Vector3 m_test_Pos;
    PhysicsStaticObject physicsStaticObject;
    PhysicsStaticObject physicsStaticObject_Wall;
    Vector3 m_pos;  //�|�W�V����
};

