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
        //���C�������_�����O�^�[�Q�b�g���쐬����
        mainRenderTarget.Create(
            1280,
            720,
            1,
            1,
            //�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            DXGI_FORMAT_D32_FLOAT
        );
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        m_shadowMap.Create(
            2048,//�����̐��l���グ��Ɖe�̉f��ꏊ���L���Ȃ�
            2048,//�����̐��l���グ��Ɖe�̉f��ꏊ���L���Ȃ�
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

        //�V���h�E�}�b�v�p�����_�����O�^�[�Q�b�g���g�p�\�ɂȂ�܂őҋ@
        renderContext.WaitUntilToPossibleSetRenderTarget(m_shadowMap);
        //�����_�����O�^�[�Q�b�g��shadowMap�ɕύX
        renderContext.SetRenderTargetAndViewport(m_shadowMap);
        //�����_�����O�^�[�Q�b�g���N���A
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


        //���C�������_�����O�^�[�Q�b�g���g�p�\�ɂȂ�܂őҋ@
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //�����_�����O�^�[�Q�b�g��mainRenderTarfet�ɕύX
        //�u���[���Ń��f����\�����I�������̉���e�N�X�`���Ƃ��Ďg������
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //�����_�����O�^�[�Q�b�g���N���A
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

        // �o�^����Ă���`��I�u�W�F�N�g���N���A
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