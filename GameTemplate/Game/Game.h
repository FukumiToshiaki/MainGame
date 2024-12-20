#pragma once
class Map;
class Player;
class PlayerCamera;
class Light_Test;
class Enemy_Shield;
class Enemy_Sky;
class Enemy_Melee;
class Enemy_Long;
class Enemy_Boss;
class BossPattern;
class Game : public IGameObject
{
public:
	Game() {};
	~Game();
	bool Start() override;
	void Update() override;
	void GameOverState();
	void GameClearState();
	void Render(RenderContext& rc) override;
	//�Q�[���̃X�e�[�g
	enum EnGameState {
		enIdle,
		enGameClear,
		enGameOver,
	};
private:
	EnGameState m_gameState = enIdle;	//�Q�[���̃X�e�[�g

	Model m_model;			// ���f��
	Vector3 m_pos;		// ���W
	Quaternion m_rotation;	// ��]
	Sprite m_sprite;	// �X�v���C�g
	Skeleton m_skeleton;	// �X�P���g��
	ModelRender m_modelRender;
	Map* m_map = nullptr;
	Player* m_player = nullptr;
	PlayerCamera* m_playerCamera = nullptr;
	Light_Test* m_LightTest = nullptr;
	Enemy_Shield* m_enemy_Shield = nullptr;
	Enemy_Melee* m_enemy_melee= nullptr;
	Enemy_Long* m_enemy_Long = nullptr;
	Enemy_Sky* m_enemy_Sky = nullptr;
	BossPattern* m_enemy_Boss = nullptr;
	//BossPattern* m_bossPattren = nullptr;
	Vector3						m_forward = Vector3::AxisZ;
	std::vector<SPointLight*>	m_pointLightList;			//�|�C���g���C�g�B
};

