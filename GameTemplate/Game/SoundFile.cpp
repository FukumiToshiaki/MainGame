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
	//�ߐڍU��
	g_soundEngine->ResistWaveFileBank(
		enSoundBitAttack, "Assets/sound/BitAttack.wav");
	//�K�[�h�̃m�b�N�o�b�N
	g_soundEngine->ResistWaveFileBank(
		enSoundDefense, "Assets/sound/Defense.wav");
	//�K�[�h�u���C�N
	g_soundEngine->ResistWaveFileBank(
		enSoundGuardBreak, "Assets/sound/GuardBreak.wav");
	//����
	g_soundEngine->ResistWaveFileBank(
		enSoundRun, "Assets/sound/Run.wav");
	//����
	g_soundEngine->ResistWaveFileBank(
		enSoundWalk, "Assets/sound/Walk.wav");
	//�_�b�V���U��
	g_soundEngine->ResistWaveFileBank(
		enSoundWalkAttack, "Assets/sound/WalkAttack.wav");



}

void SoundFile::BossSoundFile()
{
	//�{�X�̉H�΂����̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(
		enSoundFly, "Assets/sound/Fly.wav");
	//�{�X�̊���ːi�̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(
		enSoundFlyAttack, "Assets/sound/FlyAttack.wav");
	//�{�X�̒��n�̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(
		enSoundLanding, "Assets/sound/Landing.wav");
	//���K�̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(
		enSoundScream, "Assets/sound/Scream.wav");
	//�{�X�̐K���U���̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(
		enSoundTail, "Assets/sound/Tail.wav");
	//�{�X�̃u���X�̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(
		enSoundShoot, "Assets/sound/Shoot.wav");

}

void SoundFile::BossBattleSoundFile()
{
	//�{�X��BGM�̓ǂݍ���
	g_soundEngine->ResistWaveFileBank(
		enSoundBoss, "Assets/sound/Boss_LastBattle.wav");
}

