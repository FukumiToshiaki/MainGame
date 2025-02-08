#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"
#include "Bloom.h"

namespace nsK2EngineLow {

    RenderingEngine::RenderingEngine()
    {

    }
    RenderingEngine::~RenderingEngine()
    {

    }

    void RenderingEngine::Init()
    {
        //メインレンダリングターゲットを作成する
        mainRenderTarget.Create(
            1280,
            720,
            1,
            1,
            //カラーバッファーのフォーマットを32bit浮動小数点にしている
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            DXGI_FORMAT_D32_FLOAT
        );
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        m_shadowMap.Create(
            2048,//ここの数値を上げると影の映る場所が広くなる
            2048,//ここの数値を上げると影の映る場所が広くなる
            1,
            1,
            DXGI_FORMAT_R32_FLOAT,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );

        m_bloom.Init(mainRenderTarget);

        SpriteInitData resultSpData;
        resultSpData.m_fxFilePath = "Assets/shader/sprite.fx";
        resultSpData.m_width = g_graphicsEngine->GetFrameBufferWidth();
        resultSpData.m_height = g_graphicsEngine->GetFrameBufferHeight();
        resultSpData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
        //resultSpData.m_colorBufferFormat[0] = g_graphicsEngine->GetRen
        m_result.Init(resultSpData);
    }

    void RenderingEngine::Execute(RenderContext& rc)
    {

        auto& renderContext = g_graphicsEngine->GetRenderContext();

        //シャドウマップ用レンダリングターゲットが使用可能になるまで待機
        renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
        //レンダリングターゲットをshadowMapに変更
        renderContext.SetRenderTargetAndViewport(m_shadowMap);
        //レンダリングターゲットをクリア
        renderContext.ClearRenderTargetView(m_shadowMap);

        RenderShadowMap(rc);

        renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadowMap);

        ///////////////////////////////////////////////////////////////////////////
        //Sprite shadowSP;

        //SpriteInitData SPInitData;

        //SPInitData.m_fxFilePath = "Assets/shader/sprite.fx";

        //SPInitData.m_width = 1024;
        //SPInitData.m_height = 1024;

        //SPInitData.m_textures[0] = &m_shadowMap.GetRenderTargetTexture();

        //shadowSP.Init(SPInitData);

        //shadowSP.Update({ 600.0f,300.0f,0.0f }, Quaternion::Identity, { 0.3f,0.3f,0.3f });

        /////////////////////////////////////////////////////////////////////////////////////////////


        //メインレンダリングターゲットが使用可能になるまで待機
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //レンダリングターゲットをmainRenderTarfetに変更
        //ブルームでモデルを表示し終わった後の画をテクスチャとして使うため
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //レンダリングターゲットをクリア
        renderContext.ClearRenderTargetView(mainRenderTarget);

        PreRender2D(rc);

        Render3DModel(rc);

        EffectEngine::GetInstance()->Draw();

        m_bloom.Execution(mainRenderTarget);

        renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

        renderContext.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

        m_result.Draw(rc);

        Render2D(rc);

        //shadowSP.Draw(renderContext);

        // 登録されている描画オブジェクトをクリア
        m_renderObjects.clear();
    }

    void RenderingEngine::Render3DModel(RenderContext& rc)
    {
        for (auto& renderObj : m_renderObjects)
        {
            renderObj->OnRenderModel(rc);
        }
    }

    void RenderingEngine::Render2D(RenderContext& rc)
    {
        for (auto& renderObj : m_renderObjects)
        {
            renderObj->OnRender2D(rc);
        }
    }

    void RenderingEngine::PreRender2D(RenderContext& rc)
    {
        for (auto& renderObj : m_renderObjects)
        {
            renderObj->OnPreRender2D(rc);
        }
    }

    void RenderingEngine::RenderShadowMap(RenderContext& rc)
    {
        for (auto& renderObj : m_renderObjects)
        {
            renderObj->OnRenderShadowMap(rc, g_Light->GetLightData()->mPVL);
        }
    }

}