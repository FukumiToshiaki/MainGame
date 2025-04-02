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
#include "Time_Limit_UI.h"
#include "Player_HP_UI.h"
#include "Butten_UI.h"
#include "Boss_HP_UI.h"
#include "Countdown.h"
#include "SoundManager.h"

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
	//DeleteGO(m_time_Limit_UI);
	DeleteGO(m_player_HP_UI);
	//DeleteGO(m_butten_UI);
	DeleteGO(m_boss_HP_UI);

}
bool Game::Start()
{
	//m_countdown = NewGO<Countdown>(0, "countdown");
	m_player_HP_UI = NewGO<Player_HP_UI>(0, "player_hp_ui");
	m_boss_HP_UI = NewGO<Boss_HP_UI>(0, "boss_hp_ui");
	m_map = NewGO<Map>(0,"map");
	//m_butten_UI = NewGO<Butten_UI>(0,"butten_ui");
	m_playerCamera = NewGO<PlayerCamera>(0);
	m_player = NewGO<Player>(0, "player");
	//m_enemy_Shield = NewGO<Enemy_Shield>(0, "enemy_shield");
	//m_enemy_melee = NewGO<Enemy_Melee>(0, "enemy_melee");
	//m_enemy_Sky = NewGO<Enemy_Sky>(0, "enemy_sky");
	//m_enemy_Long = NewGO<Enemy_Long>(0, "enemy_long");
	//m_enemy_Boss = NewGO<Enemy_Boss>(0, "enemy_boss");
	m_enemy_Boss = NewGO<BossPattern>(0, "enemy_boss");
	//m_time_Limit_UI = NewGO<Time_Limit_UI>(0, "time_limit");
	//m_bossFlyPoint.Update({ 0.0f,0.0f,0.0f });

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}


void Game::Update()
{
	if (m_enemy_Boss->GetHP() <= 0) {
		m_gameState = enGameClear;
	}
	if (m_player->GetHP() <= 0.0f) {
		m_gameState = enGameOver;
	}
	//if (m_time_Limit_UI->GetTime_Limit() < 0) {
	//	m_gameState = enTimeOver;
	//}
	switch (m_gameState)
	{
	case Game::enTimeOver:
		TimeOver();
		break;
	case Game::enGameClear:
		GameClearState();
		break;
	case Game::enGameOver:
		GameOverState();
		break;
	}
	m_bossFlyPoint.Update(m_player->Get_PlayerPos());
}

//void Game::BGM()
//{
//}

void Game::GameOverState()
{
	if (m_player->GetisOver()) {
		m_gameTime -= g_gameTime->GetFrameDeltaTime();
		if (m_gameTime<=0) {
			g_soundManager->StopSound(enSoundBoss);
			GameOver* gameOver = NewGO<GameOver>(0, "gameover");
			DeleteGO(this);
		}
	}
}

void Game::GameClearState()
{
	m_enemy_Boss->ChangeState(Enemy_Boss::enState_Die);
	if (m_enemy_Boss->GetisClear()) {
		m_gameTime -= g_gameTime->GetFrameDeltaTime();
		if (m_gameTime <= 0) {
			g_soundManager->StopSound(enSoundBoss);
			GameClear* gameClear = NewGO<GameClear>(0, "gameclear");
			DeleteGO(this);
		}
	}
}

void Game::TimeOver()
{
		GameOver* gameOver = NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}