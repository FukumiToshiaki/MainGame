#pragma once

#include "BossFlyPoint.h"

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
class Time_Limit_UI;
class Game : public IGameObject
{
public:
	Game() {};
	~Game();
	bool Start() override;
	void Update() override;
	void GameOverState();
	void GameClearState();
	void TimeOver();
	void Render(RenderContext& rc) override;
	//ゲームのステート
	enum EnGameState {
		enNormal,
		enTimeOver,
		enGameClear,
		enGameOver,
	};

	BossFlyPoint* GetBossFlyPoint()
	{
		return &m_bossFlyPoint;
	}
private:
	EnGameState m_gameState = enNormal;	//ゲームのステート
	BossFlyPoint m_bossFlyPoint;

	Model m_model;			// モデル
	Vector3 m_pos;		// 座標
	Quaternion m_rotation;	// 回転
	Sprite m_sprite;	// スプライト
	Skeleton m_skeleton;	// スケルトン
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
	Time_Limit_UI* m_time_Limit_UI = nullptr;
	//BossPattern* m_bossPattren = nullptr;
	Vector3						m_forward = Vector3::AxisZ;
	std::vector<SPointLight*>	m_pointLightList;			//ポイントライト。
};

