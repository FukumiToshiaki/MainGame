#pragma once
namespace nsK2EngineLow {
	/// <summary>
/// �T�E���h�̖��O
/// </summary>
	enum EnSoundName
	{
		///�v���C���[
		//�ߐڍU��
		enSoundBitAttack,
		//�_�b�V���A�^�b�N
		enSoundWalkAttack,
		//�K�[�h�u���C�N
		enSoundGuardBreak,
		//�h��
		enSoundDefense,
		//����
		enSoundRun,
		//����
		enSoundWalk,

		///�{�X
		//�H�΂���
		enSoundFly,
		//����ːi
		enSoundFlyAttack,
		//���n
		enSoundLanding,
		//���K
		enSoundScream,
		//�K���U��
		enSoundTail,
		//�u���X
		enSoundShoot,

		/// <summary>
		/// �{�X��
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
		/// �T�E���h�\�[�X��ǂݍ��݁A�Đ�
		/// </summary>
		/// <param name="soundName">�ǂݍ��݂����T�E���h�\�[�X��enum�̌^</param>
		/// <param name="volume">����</param>
		/// <param name="Sound3DFlag">3D�T�E���h�ɂ��邩</param>
		/// <param name="roopFlag">���[�v���邩</param>
		/// <param name="bgmFlag">BGM�Ȃ̂�</param>
		/// <param name="soundPosition">���̍��W�B3D�T�E���h���g���Ƃ��ɐݒ�</param>
		void InitAndPlaySoundSource(
			EnSoundName soundName,
			float volume = 5.0f,
			bool Sound3DFlag = false,
			bool roopFlag = false,
			bool bgmFlag = false,
			Vector3 soundPosition = g_vec3Zero
		);

		/// <summary>
		/// �T�E���h�\�[�X�����X�g�ɒǉ�
		/// </summary>
		/// <param name="soundSource">�ǉ�����T�E���h�\�[�X</param>
		void AddSoundSourceList(SoundSource* addSoundSource);
		/// <summary>
		/// �T�E���h�\�[�X�����X�g����폜
		/// </summary>
		/// <param name="elaseSoundSource">�폜����T�E���h�\�[�X</param>
		void EraseSoundSourceList(SoundSource* elaseSoundSource);

		/// <summary>
		/// �w�肵���T�E���h�\�[�X�̃X�g�b�v
		/// </summary>
		/// <param name="soundName"></param>
		void StopSound(EnSoundName soundName);
		/// <summary>
		/// ���X�g�ɓ����Ă���S�ẴT�E���h�\�[�X�̃X�g�b�v
		/// </summary>
		void StopAllSound();

		/// <summary>
		/// ���X�g�ɓ����Ă���T�E���h���ꎞ��~
		/// </summary>
		void PauseAllSound();

		/// <summary>
		/// ���X�g�ɓ����Ă���T�E���h���v���C
		/// </summary>
		void PlayAllSound();

		/// <summary>
		/// ���X�g�ɓ����Ă���T�E���h�\�[�X���擾
		/// </summary>
		/// <param name="soundName"></param>
		SoundSource* GetSoundSource(EnSoundName soundName);

		/// <summary>
		/// �T�E���h�\�[�X�̉��ʂ�ݒ肷��
		/// </summary>
		/// <param name="mulVolume">�|���鉹��</param>
		/// <param name="bgmFlag">BGM�t���O�Btrue�Ȃ�BGM�̉��ʂ�ݒ�Afalse�Ȃ�BGM�ȊO��ݒ�</param>
		void SetSoundVolume(float mulVolume, bool bgmFlag);

		/// <summary>
		/// �S�ẴT�E���h�\�[�X�f�t�H���g�̉��ʂɕύX����
		/// </summary>
		void MakeAllSoundDefaultVolume();

		/// <summary>
		/// �f�t�H���g�̌��ʉ��{�����[�����擾
		/// </summary>
		/// <returns></returns>
		const float& GetDefaultSEVolume() const
		{
			return m_defaultSEVolume;
		}
		/// <summary>
		/// �f�t�H���g��BGM�{�����[�����擾
		/// </summary>
		/// <returns></returns>
		const float& GetDefaultBGVolume() const
		{
			return m_defaultBGMVolume;
		}
		/// <summary>
		/// ���ʉ��̃{�����[�����擾
		/// </summary>
		/// <returns></returns>
		const float& GetSEVolume() const
		{
			return m_seVolume;
		}
		/// <summary>
		/// BGM�̃{�����[�����擾
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




