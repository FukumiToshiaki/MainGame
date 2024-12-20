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
    ModelRender m_modelRender_Test;
    Vector3 m_test_Pos;
    PhysicsStaticObject physicsStaticObject;
    Vector3 m_pos;  //�|�W�V����
};

