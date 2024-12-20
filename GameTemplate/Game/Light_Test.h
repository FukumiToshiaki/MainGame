#pragma once
class Light_Test : public IGameObject
{
public:
	Light_Test() {};
	~Light_Test() {};
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Light_Point m_pointLightList;
};

