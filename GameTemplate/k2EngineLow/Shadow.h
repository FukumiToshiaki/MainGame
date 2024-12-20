#pragma once

namespace nsK2EngineLow {
	class Shadow
	{
	public:
		Shadow();
		void ShadowMap();

		struct shadow
		{
			Vector3 mLVP;
		};

		struct Shadow_Init
		{
			shadow m_shadow;
			ModelInitData ShadowModelInitData;
			Model ShadowModel;
			Camera lightCamera;
			RenderTarget shadowMap; 
			Model bgModel;
		};
		
		Shadow_Init& Getshadow_Init()
		{
			return m_shadow_Init;
		}
	private:
		Shadow_Init m_shadow_Init;
	};
}

