#include "k2EngineLowPreCompile.h"
#include "Shadow.h"
#include "k2EngineLow.h"
#include "Light/Light.h"

namespace nsK2EngineLow {
	Shadow::Shadow() {
		ShadowMap();
	}

	void Shadow::ShadowMap()
	{
        auto& renderContext = g_graphicsEngine->GetRenderContext();

		//シャドウマップ描画用のレンダリングターゲットを作成する
        //カラーバッファーのクリアカラー
        //今回はカラーバッファーは真っ白にする
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        m_shadow_Init.shadowMap.Create(
            1024,// 【注目】レンダリングターゲットの横幅
            1024,// 【注目】レンダリングターゲットの縦幅
            1,
            1,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );
        //影描画用のライトカメラを作成する

        //カメラの位置を設定。これはライトの位置
        m_shadow_Init.lightCamera.SetPosition(0, 600, 0);
        
        //カメラの注視点を設定。これがライトが照らしている場所
        m_shadow_Init.lightCamera.SetTarget(0, 0, 0);

        //上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
        m_shadow_Init.lightCamera.SetUp(1, 0, 0);

        //今回のサンプルでは画角を狭めにしておく
        m_shadow_Init.lightCamera.SetViewAngle(Math::DegToRad(20.0f));
        //ライトビュープロジェクション行列を計算している
        m_shadow_Init.lightCamera.Update();

        //シャドウマップ描画用のモデルを用意する

        //シャドウマップ描画用のシェーダーを指定する
        m_shadow_Init.ShadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
        m_shadow_Init.ShadowModelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
        m_shadow_Init.ShadowModel.Init(m_shadow_Init.ShadowModelInitData);
        m_shadow_Init.ShadowModel.UpdateWorldMatrix(
            { 0, 50, 0 },
            g_quatIdentity,
            g_vec3One
        );

        //影を受ける背景モデルを初期化
        ModelInitData bgModelInitData;

        //シャドウレシーバー（影が落とされるモデル）用のシェーダーを指定する
        bgModelInitData.m_fxFilePath = "Assets/shader/shadowReciev.fx";

        //シャドウマップを拡張SRVに設定する
        bgModelInitData.m_expandShaderResoruceView[0] = &m_shadow_Init.shadowMap.GetRenderTargetTexture();

        //ライトビュープロジェクション行列を拡張定数バッファーに設定する
        bgModelInitData.m_expandConstantBuffer = (void*)&m_shadow_Init.lightCamera.GetViewProjectionMatrix();
        bgModelInitData.m_expandConstantBufferSize = sizeof(m_shadow_Init.lightCamera.GetViewProjectionMatrix());
        bgModelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";

        Model bgModel;
        bgModel.Init(bgModelInitData);

        //影を生成したいモデルをシャドウマップに描画する
        //レンダリングターゲットをシャドウマップに変更する
        renderContext.WaitUntilToPossibleSetRenderTarget(m_shadow_Init.shadowMap);
        renderContext.SetRenderTargetAndViewport(m_shadow_Init.shadowMap);
        renderContext.ClearRenderTargetView(m_shadow_Init.shadowMap);
	
        //影モデルを描画
        m_shadow_Init.ShadowModel.Draw(renderContext, m_shadow_Init.lightCamera);

        //書き込み完了待ち
        renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadow_Init.shadowMap);
                // 通常レンダリング
        // レンダリングターゲットをフレームバッファに戻す
        renderContext.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

        //影を受ける背景を描画
        bgModel.Draw(renderContext);

    }
}