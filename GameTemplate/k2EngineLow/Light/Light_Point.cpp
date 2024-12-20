#include "k2EngineLowPreCompile.h"
#include "Light_Point.h"

namespace nsK2EngineLow {

	void Light_Point::Init()
	{
		if (m_pointLight == nullptr)
		{
			m_pointLight = g_Light->NewPointLight();
		}
	}

	Light_Point::~Light_Point()
	{
		g_Light->DeletePointLight(m_pointLight);
	}
}
