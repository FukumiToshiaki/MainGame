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

		//�V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬����
        //�J���[�o�b�t�@�[�̃N���A�J���[
        //����̓J���[�o�b�t�@�[�͐^�����ɂ���
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        m_shadow_Init.shadowMap.Create(
            1024,// �y���ځz�����_�����O�^�[�Q�b�g�̉���
            1024,// �y���ځz�����_�����O�^�[�Q�b�g�̏c��
            1,
            1,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );
        //�e�`��p�̃��C�g�J�������쐬����

        //�J�����̈ʒu��ݒ�B����̓��C�g�̈ʒu
        m_shadow_Init.lightCamera.SetPosition(0, 600, 0);
        
        //�J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ
        m_shadow_Init.lightCamera.SetTarget(0, 0, 0);

        //�������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���
        m_shadow_Init.lightCamera.SetUp(1, 0, 0);

        //����̃T���v���ł͉�p�����߂ɂ��Ă���
        m_shadow_Init.lightCamera.SetViewAngle(Math::DegToRad(20.0f));
        //���C�g�r���[�v���W�F�N�V�����s����v�Z���Ă���
        m_shadow_Init.lightCamera.Update();

        //�V���h�E�}�b�v�`��p�̃��f����p�ӂ���

        //�V���h�E�}�b�v�`��p�̃V�F�[�_�[���w�肷��
        m_shadow_Init.ShadowModelInitData.m_fxFilePath = "Assets/shader/shadow.fx";
        m_shadow_Init.ShadowModelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
        m_shadow_Init.ShadowModel.Init(m_shadow_Init.ShadowModelInitData);
        m_shadow_Init.ShadowModel.UpdateWorldMatrix(
            { 0, 50, 0 },
            g_quatIdentity,
            g_vec3One
        );

        //�e���󂯂�w�i���f����������
        ModelInitData bgModelInitData;

        //�V���h�E���V�[�o�[�i�e�����Ƃ���郂�f���j�p�̃V�F�[�_�[���w�肷��
        bgModelInitData.m_fxFilePath = "Assets/shader/shadowReciev.fx";

        //�V���h�E�}�b�v���g��SRV�ɐݒ肷��
        bgModelInitData.m_expandShaderResoruceView[0] = &m_shadow_Init.shadowMap.GetRenderTargetTexture();

        //���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�[�ɐݒ肷��
        bgModelInitData.m_expandConstantBuffer = (void*)&m_shadow_Init.lightCamera.GetViewProjectionMatrix();
        bgModelInitData.m_expandConstantBufferSize = sizeof(m_shadow_Init.lightCamera.GetViewProjectionMatrix());
        bgModelInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";

        Model bgModel;
        bgModel.Init(bgModelInitData);

        //�e�𐶐����������f�����V���h�E�}�b�v�ɕ`�悷��
        //�����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX����
        renderContext.WaitUntilToPossibleSetRenderTarget(m_shadow_Init.shadowMap);
        renderContext.SetRenderTargetAndViewport(m_shadow_Init.shadowMap);
        renderContext.ClearRenderTargetView(m_shadow_Init.shadowMap);
	
        //�e���f����`��
        m_shadow_Init.ShadowModel.Draw(renderContext, m_shadow_Init.lightCamera);

        //�������݊����҂�
        renderContext.WaitUntilFinishDrawingToRenderTarget(m_shadow_Init.shadowMap);
                // �ʏ탌���_�����O
        // �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɖ߂�
        renderContext.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        renderContext.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());

        //�e���󂯂�w�i��`��
        bgModel.Draw(renderContext);

    }
}