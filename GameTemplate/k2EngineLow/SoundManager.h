#pragma once
namespace nsK2EngineLow {
	/// <summary>
/// サウンドの名前
/// </summary>
	enum EnSoundName
	{
		///プレイヤー
		//近接攻撃
		enSoundBitAttack,
		//ダッシュアタック
		enSoundWalkAttack,
		//ガードブレイク
		enSoundGuardBreak,
		//防御
		enSoundDefense,
		//走る
		enSoundRun,
		//歩く
		enSoundWalk,

		///ボス
		//羽ばたき
		enSoundFly,
		//滑空突進
		enSoundFlyAttack,
		//着地
		enSoundLanding,
		//咆哮
		enSoundScream,
		//尻尾攻撃
		enSoundTail,
		//ブレス
		enSoundShoot,

		/// <summary>
		/// ボス戦
		/// </summary>
		enSoundBoss,

		enSoundName_Num
	};
	class SoundManager :public Noncopyable
	{
	public:
		SoundManager();
		~SoundManager();

		/// <summary>
		/// サウンドソースを読み込み、再生
		/// </summary>
		/// <param name="soundName">読み込みたいサウンドソースのenumの型</param>
		/// <param name="volume">音量</param>
		/// <param name="Sound3DFlag">3Dサウンドにするか</param>
		/// <param name="roopFlag">ループするか</param>
		/// <param name="bgmFlag">BGMなのか</param>
		/// <param name="soundPosition">音の座標。3Dサウンドを使うときに設定</param>
		void InitAndPlaySoundSource(
			EnSoundName soundName,
			float volume = 5.0f,
			bool Sound3DFlag = false,
			bool roopFlag = false,
			bool bgmFlag = false,
			Vector3 soundPosition = g_vec3Zero
		);

		/// <summary>
		/// サウンドソースをリストに追加
		/// </summary>
		/// <param name="soundSource">追加するサウンドソース</param>
		void AddSoundSourceList(SoundSource* addSoundSource);
		/// <summary>
		/// サウンドソースをリストから削除
		/// </summary>
		/// <param name="elaseSoundSource">削除するサウンドソース</param>
		void EraseSoundSourceList(SoundSource* elaseSoundSource);

		/// <summary>
		/// 指定したサウンドソースのストップ
		/// </summary>
		/// <param name="soundName"></param>
		void StopSound(EnSoundName soundName);
		/// <summary>
		/// リストに入っている全てのサウンドソースのストップ
		/// </summary>
		void StopAllSound();

		/// <summary>
		/// リストに入っているサウンドを一時停止
		/// </summary>
		void PauseAllSound();

		/// <summary>
		/// リストに入っているサウンドをプレイ
		/// </summary>
		void PlayAllSound();

		/// <summary>
		/// リストに入っているサウンドソースを取得
		/// </summary>
		/// <param name="soundName"></param>
		SoundSource* GetSoundSource(EnSoundName soundName);

		/// <summary>
		/// サウンドソースの音量を設定する
		/// </summary>
		/// <param name="mulVolume">掛ける音量</param>
		/// <param name="bgmFlag">BGMフラグ。trueならBGMの音量を設定、falseならBGM以外を設定</param>
		void SetSoundVolume(float mulVolume, bool bgmFlag);

		/// <summary>
		/// 全てのサウンドソースデフォルトの音量に変更する
		/// </summary>
		void MakeAllSoundDefaultVolume();

		/// <summary>
		/// デフォルトの効果音ボリュームを取得
		/// </summary>
		/// <returns></returns>
		const float& GetDefaultSEVolume() const
		{
			return m_defaultSEVolume;
		}
		/// <summary>
		/// デフォルトのBGMボリュームを取得
		/// </summary>
		/// <returns></returns>
		const float& GetDefaultBGVolume() const
		{
			return m_defaultBGMVolume;
		}
		/// <summary>
		/// 効果音のボリュームを取得
		/// </summary>
		/// <returns></returns>
		const float& GetSEVolume() const
		{
			return m_seVolume;
		}
		/// <summary>
		/// BGMのボリュームを取得
		/// </summary>
		/// <returns></returns>
		const float& GetBGMVolume() const
		{
			return m_bgmVolume;
		}

	private:
		std::vector<SoundSource*> m_soundSourceList;

		const float m_defaultSEVolume = 2.0f;
		const float m_defaultBGMVolume = 4.0f;

		float m_seVolume = m_defaultSEVolume;
		float m_bgmVolume = m_defaultBGMVolume;

	};

	extern SoundManager* g_soundManager;
}




