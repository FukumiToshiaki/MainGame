#pragma once
#include "k2EngineLowPreCompile.h"
#include "k2EngineLow.h"
#include "Light/Light.h"
#include "IRender.h"


namespace nsK2EngineLow {
	class ModelRender : public IRender
	{
	public:
		ModelRender();
		~ModelRender();

		struct tsts
		{
		public:
			Structure_Light m_light;
			Matrix m_mt;
		};

		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="tkmfilePath">���f���̃t�@�C���p�X</param>
		/// <param name="animationClips">�A�j���[�V�����N���b�v</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐�</param>
		/// <param name="enModelUpAxis">���f���̏����</param>
		/// <param name="dithering">�f�B�U�����O�t���O�Ature�Ȃ�f�B�U�����O���s��</param>
		/// <param name="isRecieverShadow">�e�𗎂Ƃ������߂�t���O�Ature�Ȃ�e��������</param>
		void Init(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool dithering = false,
			bool isRecieveShadow = false
		);

		void InitNormalModel(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ,
			bool dithering = false,
			bool isRecieveShadow = false
		);

		void InitShadowModel(
			const char* tkmFilePath,
			EnModelUpAxis modelUpAxis
		);

		// �X�P���g���̏�����
		void InitSkeleton(const char* filePath);

		// �A�j���[�V�����̏�����
		void InitAnimation(
			AnimationClip* animationClips,
			int numAnimationClips
		);

		// �A�j���[�V�����Đ�
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}

		// �A�j���[�V�����Đ���
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// �A�j���[�V�����Đ��̑��x��ݒ�
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		//�A�j���[�V�����C�x���g
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		// �X�V����
		void Update();

		//Bloom
		void InitBloom();
		
		//���W��ݒ�B
		void SetPosition(Vector3 pos)
		{
			m_pos = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}

		//��]��ݒ�
		void SetRotation(Quaternion rot)
		{
			m_rot = rot;
		}

		//�g�嗦��ݒ�B
		void SetScale(Vector3 scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}

		Model& GetModel()
		{
			return m_model;
		}

		//�{�[�����K��
		Bone* GetBone(int boneNo)const
		{
			return m_skeleton.GetBone(boneNo);
		}

		int FindBoneID(const wchar_t* boneName)const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		//�`�揈��
		void Draw(RenderContext& rc);

		//3D���f���̕`�揈��
		void OnRenderModel(RenderContext& rc) override;

		//�V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈��
		void OnRenderShadowMap(RenderContext& rc, const Matrix& lvpMatrix) override;

		void SetShadowChasterFlag(bool flag)
		{
			m_isShadowChaster = flag;
		}

	private:
		Model m_model;
		Skeleton		m_skeleton;
		AnimationClip* m_animationClips = nullptr;
		int				m_numAnimationClips = 0;
		Animation		m_animation;
		Bloom* m_bloom = nullptr;
		Vector3 m_pos = Vector3::Zero;
		Quaternion m_rot = Quaternion::Identity;
		Vector3 m_scale = Vector3::One;

		float m_animationSpeed = 1.0f;			//�A�j���[�V�����̍Đ��X�s�[�h


		//�V���h�E�}�b�v�֘A

		Model m_shadowModel;

		tsts m_tsts;

		bool m_isShadowChaster = true;		//�e�𗎂Ƃ����Ǘ�����t���O
	};

}