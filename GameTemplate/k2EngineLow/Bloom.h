#pragma once

const int NUM_DIRECTIONAL_LIGHT = 4; // �f�B���N�V�������C�g�̐�
const int NUM_WEIGHTS = 8;

namespace nsK2EngineLow {
        /// <summary>
        /// �f�B���N�V�������C�g
        /// </summary>
        struct DirectionalLight
        {
            Vector3 direction;  // ���C�g�̕���
            float pad0;         // �p�f�B���O
            Vector4 color;      // ���C�g�̃J���[
        };

        /// <summary>
        /// ���C�g�\����
        /// </summary>
        struct Bloom_Light
        {
            DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT]; // �f�B���N�V�������C�g
            Vector3 eyePos;         // �J�����̈ʒu
            float specPow;          // �X�y�L�����̍i��
            Vector3 ambinetLight;   // ����
        };

        /// <summary>
        /// �u���[�p�̃p�����[�^
        /// </summary>
        struct SBlurParam
        {
            float weights[NUM_WEIGHTS];
        };

        class Bloom : public Noncopyable
        {
        public:
            Bloom();

            //������
            void Init(RenderTarget& renderTarget);

            void Execution(RenderTarget& renderTarget);

            void Update();

            void MainRendring();

            Bloom_Light& GetBloom_Light()
            {
                return m_bloomLight;
            }

            Sprite& GetfinalSprite()
            {
                return finalSprite;
            }

            
            //Sprite& SetfinalSprite(Sprite setfinalSprite)
            //{
            //    finalSprite;
            //}
        private:
            Bloom_Light m_bloomLight;
            Sprite luminanceSprite;
            GaussianBlur gaussianBlur[4];//�K�E�V�A���u���[��������
            SpriteInitData finalSpriteInitData;
            SpriteInitData luminanceSpriteInitData;
            //SpriteInitData combineBokeImageSpriteInitData;//�{�P�摜�����p�̃X�v���C�g������������
            RenderTarget luminnceRenderTarget;
            Bloom_Light light;
            Sprite finalSprite;
            Sprite combineBokeImageSprite;
            SpriteInitData spriteInitData;
            //SpriteInitData spriteInitData_2D;
            Sprite copyToFrameBufferSprite;
            //RenderTarget mainRenderTarget;
            ModelInitData plModelInitData;
        };
}

