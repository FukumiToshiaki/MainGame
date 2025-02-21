#include "stdafx.h"
#include "SoundFile.h"
#include "SoundManager.h"
SoundFile::SoundFile()
{
	ResistAllSoundFile();
}

SoundFile::~SoundFile()
{
}

void SoundFile::ResistAllSoundFile()
{
	PlayerSoundFile();
	BossSoundFile();
	BossBattleSoundFile();
}

void SoundFile::PlayerSoundFile()
{
	//近接攻撃
	g_soundEngine->ResistWaveFileBank(
		enSoundBitAttack, "Assets/sound/BitAttack.wav");
	//ガードのノックバック
	g_soundEngine->ResistWaveFileBank(
		enSoundDefense, "Assets/sound/Defense.wav");
	//ガードブレイク
	g_soundEngine->ResistWaveFileBank(
		enSoundGuardBreak, "Assets/sound/GuardBreak.wav");
	//走る
	g_soundEngine->ResistWaveFileBank(
		enSoundRun, "Assets/sound/Run.wav");
	//歩く
	g_soundEngine->ResistWaveFileBank(
		enSoundWalk, "Assets/sound/Walk.wav");
	//ダッシュ攻撃
	g_soundEngine->ResistWaveFileBank(
		enSoundWalkAttack, "Assets/sound/WalkAttack.wav");



}

void SoundFile::BossSoundFile()
{
	//ボスの羽ばたきの読み込み
	g_soundEngine->ResistWaveFileBank(
		enSoundFly, "Assets/sound/Fly.wav");
	//ボスの滑空突進の読み込み
	g_soundEngine->ResistWaveFileBank(
		enSoundFlyAttack, "Assets/sound/FlyAttack.wav");
	//ボスの着地の読み込み
	g_soundEngine->ResistWaveFileBank(
		enSoundLanding, "Assets/sound/Landing.wav");
	//咆哮の読み込み
	g_soundEngine->ResistWaveFileBank(
		enSoundScream, "Assets/sound/Scream.wav");
	//ボスの尻尾攻撃の読み込み
	g_soundEngine->ResistWaveFileBank(
		enSoundTail, "Assets/sound/Tail.wav");
	//ボスのブレスの読み込み
	g_soundEngine->ResistWaveFileBank(
		enSoundShoot, "Assets/sound/Shoot.wav");

}

void SoundFile::BossBattleSoundFile()
{
	//ボス戦BGMの読み込み
	g_soundEngine->ResistWaveFileBank(
		enSoundBoss, "Assets/sound/Boss_LastBattle.wav");
}

