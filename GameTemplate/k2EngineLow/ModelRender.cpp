#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "Shadow.h"
#include "RenderingEngine.h"
#include "Bloom.h"

namespace nsK2EngineLow {


	ModelRender::ModelRender()
	{

	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Init(
		const char* tkmfilePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool dithering,
		bool isRecieveShadow
	)
	{
		//�X�P���g���̏�����
		InitSkeleton(tkmfilePath);

		//�A�j���[�V�����̏�����
		InitAnimation(animationClips, numAnimationClips);

		//��{�̃��f��������
		InitNormalModel(tkmfilePath, animationClips, numAnimationClips, enModelUpAxis, dithering, isRecieveShadow);

		//�V���h�E�}�b�v�`��p���f���̏�����
		InitShadowModel(tkmfilePath, enModelUpAxis);

	}

	void ModelRender::InitNormalModel(
		const char* tkmfilePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		bool dithering,
		bool isRecieveShadow
	)
	{
		ModelInitData initData;

		initData.m_tkmFilePath = tkmfilePath;

		if (dithering == false)
		{
			initData.m_fxFilePath = "Assets/shader/model.fx";
		}
		else
		{
			initData.m_fxFilePath = "Assets/shader/ditheringModel.fx";
		}

		if (isRecieveShadow == true)
		{
			initData.m_fxFilePath = "Assets/shader/shadowReciev.fx";


			initData.m_expandConstantBuffer = &(g_Light->GetSceneLight());
			initData.m_expandConstantBufferSize = sizeof(g_Light->GetSceneLight());

			//�V���h�E�}�b�v���g��SRV�ɐݒ肷��
			initData.m_expandShaderResoruceView[0] = &(g_renderingEngine->GetShadowMapRenderTarget()->GetRenderTargetTexture());
		}
		else
		{
			initData.m_expandConstantBuffer = g_Light->GetLightData();
			initData.m_expandConstantBufferSize = sizeof(Light);
		}

		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		//�X�P���g��������������Ă�����
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_modelUpAxis = enModelUpAxis;

		//�쐬�����������f�[�^�����ƂɃ��f��������������A
		m_model.Init(initData);
	}

	void ModelRender::InitShadowModel(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = tkmFilePath;
		initData.m_modelUpAxis = modelUpAxis;

		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		//initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		//initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		if (m_animationClips != nullptr) {
			//�X�P���g�����w�肷��B
			initData.m_skeleton = &m_skeleton;
		}
		
		initData.m_fxFilePath = "Assets/shader/shadow.fx";

		//�J���[�o�b�t�@�[�̃t�H�[�}�b�g�ɕύX���������̂ŁA��������ύX����
		initData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

		m_shadowModel.Init(initData);
		m_shadowModel.UpdateWorldMatrix(
			{ 0, 50, 0 },
			g_quatIdentity,
			g_vec3One
		);

		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		m_shadowModel.Init(initData);
	}

	//tkm�t�@�C���̃p�X��.tkm�̕�����.tks�ɂ��ēǂݍ��ގ���
	//��������tkm�t�@�C���p�X��tks�t�@�C���p�X��������͂���K�v�������Ȃ�
	//�����tkm�t�@�C��������t�@�C����tks�t�@�C�����Ȃ��Ɠǂݍ��߂Ȃ��B
	void ModelRender::InitSkeleton(const char* tkmFilePath)
	{
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::string skeletonFilePath = tkmFilePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips 
			);
		}
	}

	void ModelRender::Update()
	{
		//���[���h�s��X�V
		m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);

		m_shadowModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);

		//�X�P���g�����������ς݂̏ꍇ�A�X�P���g���̍X�V
		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		//�A�j���[�V������i�߂�
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::InitBloom()
	{
		//m_bloom->GetBloom_Light();
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}

	void ModelRender::OnRenderModel(RenderContext& rc)
	{
		m_model.Draw(rc);
	}

	void ModelRender::OnRenderShadowMap(RenderContext& rc, const Matrix& lvpMatrix)
	{
		if (m_isShadowChaster)
		{
			m_shadowModel.Draw(
				rc,
				g_matIdentity,
				lvpMatrix,
				1
			);
		}
	}
}
