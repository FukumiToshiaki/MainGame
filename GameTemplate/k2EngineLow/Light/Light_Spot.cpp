#include "k2EngineLowPreCompile.h"
#include "Light_Spot.h"

namespace nsK2EngineLow {

	void Light_Spot::Init()
	{
		if (m_spotLight == nullptr)
		{
			m_spotLight = g_Light->NewSpotLight();
		}
	}

	Light_Spot::~Light_Spot()
	{
		g_Light->DeleteSpotLight(m_spotLight);
	}


}
