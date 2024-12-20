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
		//スケルトンの初期化
		InitSkeleton(tkmfilePath);

		//アニメーションの初期化
		InitAnimation(animationClips, numAnimationClips);

		//基本のモデル初期化
		InitNormalModel(tkmfilePath, animationClips, numAnimationClips, enModelUpAxis, dithering, isRecieveShadow);

		//シャドウマップ描画用モデルの初期化
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

			//シャドウマップを拡張SRVに設定する
			initData.m_expandShaderResoruceView[0] = &(g_renderingEngine->GetShadowMapRenderTarget()->GetRenderTargetTexture());
		}
		else
		{
			initData.m_expandConstantBuffer = g_Light->GetLightData();
			initData.m_expandConstantBufferSize = sizeof(Light);
		}

		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		//スケルトンが初期化されていたら
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}

		initData.m_modelUpAxis = enModelUpAxis;

		//作成した初期化データをもとにモデルを初期化する、
		m_model.Init(initData);
	}

	void ModelRender::InitShadowModel(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = tkmFilePath;
		initData.m_modelUpAxis = modelUpAxis;

		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		//initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		//initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		if (m_animationClips != nullptr) {
			//スケルトンを指定する。
			initData.m_skeleton = &m_skeleton;
		}
		
		initData.m_fxFilePath = "Assets/shader/shadow.fx";

		//カラーバッファーのフォーマットに変更が入ったので、こちらも変更する
		initData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

		m_shadowModel.Init(initData);
		m_shadowModel.UpdateWorldMatrix(
			{ 0, 50, 0 },
			g_quatIdentity,
			g_vec3One
		);

		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		m_shadowModel.Init(initData);
	}

	//tkmファイルのパスの.tkmの部分を.tksにして読み込む事で
	//いちいちtkmファイルパスとtksファイルパス両方を入力する必要が無くなる
	//代わりにtkmファイルがあるファイルにtksファイルがないと読み込めない。
	void ModelRender::InitSkeleton(const char* tkmFilePath)
	{
		//スケルトンのデータを読み込み。
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
		//ワールド行列更新
		m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);

		m_shadowModel.UpdateWorldMatrix(m_pos, m_rot, m_scale);

		//スケルトンが初期化済みの場合、スケルトンの更新
		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		//アニメーションを進める
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
