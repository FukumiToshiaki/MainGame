#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow {
    Bloom::Bloom()
    {

    }

    void Bloom::Init(RenderTarget& renderTarget)
    {
        ////���C�������_�����O�^�[�Q�b�g���쐬����
        //mainRenderTarget.Create(
        //    1280,
        //    720,
        //    1,
        //    1,
        //    //�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���
        //    DXGI_FORMAT_R32G32B32A32_FLOAT,
        //    DXGI_FORMAT_D32_FLOAT
        //);
        //�������̃��C�g��p�ӂ���
        //// �V�F�[�_�[�t�@�C�����w�肷��
        //plModelInitData.m_fxFilePath = "Assets/shader/3D.fx";

        //// ���[�U�[�g���̒萔�o�b�t�@�[�ɑ���f�[�^���w�肷��
        //plModelInitData.m_expandConstantBuffer = &light;

        //// ���[�U�[�g���̒萔�o�b�t�@�[�ɑ���f�[�^�̃T�C�Y���w�肷��
        //plModelInitData.m_expandConstantBufferSize = sizeof(light);

        //// �����_�����O����J���[�o�b�t�@�[�̃t�H�[�}�b�g���w�肷��
        //plModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;


        //�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬

        //�𑜓x�A�~�b�v�}�b�v���x��
        luminnceRenderTarget.Create(
            1280,   //�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ���
            720,    //�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ���
            1,
            1,
            //�J���[�o�b�t�@�[�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            DXGI_FORMAT_D32_FLOAT
        );

        //�P�x���o�p�̃X�v���C�g��������
        //�����������쐬����

        //�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��
        luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";

        //���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
        luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";

        //�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
        luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";

        //�X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ���
        luminanceSpriteInitData.m_width = 1280;
        luminanceSpriteInitData.m_height = 720;

        //�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
        luminanceSpriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();

        //�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
        luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
        //�쐬�����������������ƂɃX�v���C�g������������
        luminanceSprite.Init(luminanceSpriteInitData);

        //�K�E�V�A���u���[��������
    // gaussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[��������
        gaussianBlur[0].Init(&luminnceRenderTarget.GetRenderTargetTexture());
        // gaussianBlur[1]��gaussianBlur[0]�̃e�N�X�`���ɃK�E�V�A���u���[��������
        gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
        // gaussianBlur[2]��gaussianBlur[1]�̃e�N�X�`���ɃK�E�V�A���u���[��������
        gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
        // gaussianBlur[3]��gaussianBlur[2]�̃e�N�X�`���ɃK�E�V�A���u���[��������
        gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());

        //�{�P�摜�����Z��������X�v���C�g��������
        //����������ݒ肷��
        //�{�P�e�N�X�`����4���w�肷��
        finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
        finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
        finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
        finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
        // �ڂ������摜���A�ʏ��2D�Ƃ��ă��C�������_�����O�^�[�Q�b�g�ɕ`�悷��̂ŁA
        // 2D�p�̃V�F�[�_�[���g�p����
        finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
        finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

        //�𑜓x��mainRenderTarget�̕��ƍ���
        finalSpriteInitData.m_width = 1280;
        finalSpriteInitData.m_height = 720;

        //�ڂ������摜���A�ʏ��2D�Ƃ��ă��C�������_�����O�^�[�Q�b�g�ɕ`�悷��̂ŁA
        //2D�p�̃V�F�[�_�[���g�p����
        //���m�N���p�̃V�F�[�_�[���w�肷��
        spriteInitData.m_fxFilePath = "Assets/shader/2D.fx";

        //�������A���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�����Z�ɂ���
        finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;

        //�J���[�o�b�t�@�[�̃t�H�[�}�b�g�͗�ɂ���āA32�r�b�g���������_�o�b�t�@�[
        finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
        //�������������ɉ��Z�����p�̃X�v���C�g������������
        finalSprite.Init(finalSpriteInitData);

        ////�e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�[
        spriteInitData.m_textures[0] = &renderTarget.GetRenderTargetTexture();
        //�𑜓x��mainRenderTarget�̕��ƍ���
        spriteInitData.m_width = 1280;
        spriteInitData.m_height = 720;

        //// �������I�u�W�F�N�g�𗘗p���ăX�v���C�g������������
        //combineBokeImageSprite.Init(spriteInitData);
        //�������I�u�W�F�N�g���g���āA�X�v���C�g������������
        copyToFrameBufferSprite.Init(spriteInitData);
    }

    void Bloom::Execution(RenderTarget& renderTarget)
    {
        auto& renderContext = g_graphicsEngine->GetRenderContext();

        //�P�x���o
        //�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
        renderContext.WaitUntilToPossibleSetRenderTarget(luminnceRenderTarget);

        //�����_�����O�^�[�Q�b�g��ݒ�
        renderContext.SetRenderTargetAndViewport(luminnceRenderTarget);

        //�����_�����O�^�[�Q�b�g���N���A
        renderContext.ClearRenderTargetView(luminnceRenderTarget);

        //�P�x���o���s��
        luminanceSprite.Draw(renderContext);

        //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
        renderContext.WaitUntilFinishDrawingToRenderTarget(luminnceRenderTarget);

        //�K�E�V�A���u���[��4����s����
        gaussianBlur[0].ExecuteOnGPU(renderContext, 10);
        gaussianBlur[1].ExecuteOnGPU(renderContext, 10);
        gaussianBlur[2].ExecuteOnGPU(renderContext, 10);
        gaussianBlur[3].ExecuteOnGPU(renderContext, 10);

        //�{�P�摜�����C�������_�����O�^�[�Q�b�g�ɉ��Z����
        //�����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
        renderContext.WaitUntilToPossibleSetRenderTarget(renderTarget);

        //�����_�����O�^�[�Q�b�g��ݒ�
        renderContext.SetRenderTargetAndViewport(renderTarget);

        //�ŏI����
        finalSprite.Draw(renderContext);

        //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
        renderContext.WaitUntilFinishDrawingToRenderTarget(renderTarget);

        //���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
        renderContext.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        copyToFrameBufferSprite.Draw(renderContext);
    }

    void Bloom::MainRendring()
    {
    }
    void Bloom::Update()
    {

    }
}