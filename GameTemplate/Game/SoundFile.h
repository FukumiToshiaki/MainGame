#pragma once
class SoundFile
{
public:
	SoundFile();
	~SoundFile();

	/// <summary>
	/// �S�ẴT�E���h�t�@�C���̓ǂݍ���
	/// </summary>
	void ResistAllSoundFile();

private:
	///�v���C���[�̃T�E���h�t�@�C���ǂݍ���
	void PlayerSoundFile();
	///�{�X�̃T�E���h�t�@�C���ǂݍ���
	void BossSoundFile();
	///�{�X��̃T�E���h�t�@�C���ǂݍ���
	void BossBattleSoundFile();
};

