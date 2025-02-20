#pragma once
class SoundFile
{
public:
	SoundFile();
	~SoundFile();

	/// <summary>
	/// 全てのサウンドファイルの読み込み
	/// </summary>
	void ResistAllSoundFile();

private:
	///プレイヤーのサウンドファイル読み込み
	void PlayerSoundFile();
	///ボスのサウンドファイル読み込み
	void BossSoundFile();
	///ボス戦のサウンドファイル読み込み
	void BossBattleSoundFile();
};

