#pragma once
#include "Bloom.h"
/// <summary>
/// レンダリングエンジン。
/// </summary>
/// <remark>
/// K2Engineの１フレームのレンダリングの流れは次のようになっています。
/// １.ComputeAnimatedVertex
///     ワールド空間に変換済みの頂点を計算する。   
///     以降のモデル描画パスでは、このパスで計算された頂点を使い回す。
/// 　　このパスでインスタンシング描画を行うモデルの頂点バッファは１つの大きなバッファにまとめられる。
///     例えば、あるモデルをインスタンシング描画で100頂点のモデルを100体描画する設定になっている場合、
///     100頂点 × 100の1万頂点を記憶できる頂点バッファが作られる。
///     頂点バッファをまとめる理由はDXRの高速化のため。
///     DXRではレイトレワールドに登録するオブジェクトの数が多くなると、効率的なBVHが構築できなくなり、
///     大きく速度が低下する。このオブジェクトを１つの頂点バッファに纏めることで大幅な高速化が可能となる。
/// 
/// 2. シャドウマップの作成
///     カスケードシャドウ方を利用して４つのライトからのシャドウマップを作成する。
///     そのため、４つのライト　×　３枚のシャドウマップ(近距離用、中距離用、遠距離用)の合計12枚のシャドウマップが作成される。
/// 
/// 3. ZPrepass
///     ライトカリングのためのZPrepass。
///     無駄なピクセル描画を避けるためではなく、深度テクスチャを作成するために存在しているパス。
///     後述するG-Bufferの深度テクスチャを使えばいいように感じるが、
///     ディファードとフォワードの両方の深度値が書き込まれたテクスチャが必要だったため追加。
/// 
/// 4. ライトカリング
///     タイルごとのポイントライトとスポットライトの番号リストを作成。
/// 
/// 5. G-Bufferへのレンダリング
///     G-Bufferはアルベド&深度値、法線、メタリック&シャドウ&Smoothの３枚。
/// 
/// 6. レイトレーシングで映り込み画像を作成する。
///     NVIDIAのRTXシリーズのGPUが乗っている場合、レイトレを用いて各オブジェクトへの映り込み画像を生成する。
///     このパスはNVIDIAのRTXシリーズでしか通常は使えない。
///     ただし、k2EngineLow\k2EngineLowPreCompile.hのENABLE_DXR_ON_RTX_ONLYのマクロを無効にすることで
///     DXRが利用できる一部のRTX以外のGPU（NVIDIA GTX1060など）でもレイトレを行える。
///     ただし、GTXシリーズではパフォーマンスが大きく損なわれるため、あくまでも開発用。
/// 
/// 7. ディファードライティング
///     ディズニーベースのPBRライティングが行われる。
/// 
/// 8. フォワードレンダリング
///     半透明オブジェクトや特殊なシェーディングの描画パス。
/// 
/// 9. ポストエフェクト
///     下記のポストエフェクトが実行される。
///     9.1 スクリーンスペースリフレクション(レイトレを行っている場合は処理されない。)
///     9.2 シーンの輝度計算(後述のHDRレンダリングのブルームやトーンマップで使用される。)
///     9.3 ブルーム
///     9.4 トーンマップ
///     9.5 Effekseerのエフェクト描画
///     9.6 DOF
///     9.7 FXAA + ガンマ補正
/// 
/// 10. 2D描画
/// 11. 最終画像をフレームバッファにコピー。
/// </reramk>

namespace nsK2EngineLow {
	class RenderingEngine : public Noncopyable
	{
	public:

		RenderingEngine();
		~RenderingEngine();

		void Init();

		//描画オブジェクトを追加
		void AddRenderObject(IRender* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		//3Dモデルの描画
		void Render3DModel(RenderContext& rc);

		//2D描画
		void Render2D(RenderContext& rc);

		//事前2D描画
		void PreRender2D(RenderContext& rc);

		//シャドウマップ描画処理
		void RenderShadowMap(RenderContext& rc);

		//フォント描画
		void FontRender(RenderContext& rc);

		//実行
		void Execute(RenderContext& rc);


		RenderTarget* GetShadowMapRenderTarget()
		{
			return &m_shadowMap;
		}

	private:
		std::vector< IRender* > m_renderObjects;	// 描画オブジェクトのリスト。

		RenderTarget m_shadowMap;
		RenderTarget mainRenderTarget;
		Bloom m_bloom;

		Sprite m_result;	//ポストエフェクトなどの処理を終えた最終的な画像
	};
}


