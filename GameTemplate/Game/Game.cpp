#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "PlayerCamera.h"
#include "Light_Test.h"
#include "Enemy_Shield.h"
#include "Enemy_Melee.h"
#include "Enemy_Sky.h"
#include "Enemy_Long.h"
#include "Enemy_Boss.h"
#include "GameClear.h"
#include "GameOver.h"
#include "BossPattern.h"

Game::~Game()
{
	DeleteGO(m_map);
	DeleteGO(m_player);
	DeleteGO(m_playerCamera);
	DeleteGO(m_enemy_Boss);
	DeleteGO(m_enemy_Long);
	DeleteGO(m_enemy_melee);
	DeleteGO(m_enemy_Shield);
	DeleteGO(m_enemy_Sky);
}
bool Game::Start()
{
	m_map = NewGO<Map>(0,"map");
	//m_LightTest = NewGO<Light_Test>(0);
	m_playerCamera = NewGO<PlayerCamera>(0);
	m_enemy_Shield = NewGO<Enemy_Shield>(0, "enemy_shield");
	m_enemy_melee = NewGO<Enemy_Melee>(0, "enemy_melee");
	m_enemy_Sky = NewGO<Enemy_Sky>(0, "enemy_sky");
	m_enemy_Long = NewGO<Enemy_Long>(0, "enemy_long");
	//m_enemy_Boss = NewGO<Enemy_Boss>(0, "enemy_boss");
	m_enemy_Boss = NewGO<BossPattern>(0, "enemy_boss");
	m_player = NewGO<Player>(0, "player");
	//m_modelRender.SetPosition(m_position);

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}


void Game::Update()
{
	if (m_enemy_Boss->GetHP() <= 0) {
		m_gameState = enGameClear;
	}
	if (m_player->GetHP() <= 0) {
		m_gameState = enGameOver;
	}
	switch (m_gameState)
	{
	case Game::enIdle:
		break;
	case Game::enGameClear:
		GameClearState();
		break;
	case Game::enGameOver:
		GameOverState();
		break;
	}
}

void Game::GameOverState()
{
	m_player->SetisDie(true);
	if (m_player->GetisOver()) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			GameOver* gameOver = NewGO<GameOver>(0, "gameover");
			DeleteGO(this);
		}
	}
}

void Game::GameClearState()
{
	m_enemy_Boss->SetisDie(true);
	if (m_enemy_Boss->GetisClear()) {
		if (g_pad[0]->IsTrigger(enButtonA)) {
			GameClear* gameClear = NewGO<GameClear>(0, "gameclear");
			DeleteGO(this);
		}
	}
}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}