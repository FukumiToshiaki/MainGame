#pragma once

const int NUM_DIRECTIONAL_LIGHT = 4; // ディレクションライトの数
const int NUM_WEIGHTS = 8;

namespace nsK2EngineLow {
        /// <summary>
        /// ディレクションライト
        /// </summary>
        struct DirectionalLight
        {
            Vector3 direction;  // ライトの方向
            float pad0;         // パディング
            Vector4 color;      // ライトのカラー
        };

        /// <summary>
        /// ライト構造体
        /// </summary>
        struct Bloom_Light
        {
            DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT]; // ディレクションライト
            Vector3 eyePos;         // カメラの位置
            float specPow;          // スペキュラの絞り
            Vector3 ambinetLight;   // 環境光
        };

        /// <summary>
        /// ブラー用のパラメータ
        /// </summary>
        struct SBlurParam
        {
            float weights[NUM_WEIGHTS];
        };

        class Bloom : public Noncopyable
        {
        public:
            Bloom();

            //初期化
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
            GaussianBlur gaussianBlur[4];//ガウシアンブラーを初期化
            SpriteInitData finalSpriteInitData;
            SpriteInitData luminanceSpriteInitData;
            //SpriteInitData combineBokeImageSpriteInitData;//ボケ画像合成用のスプライトを初期化する
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

