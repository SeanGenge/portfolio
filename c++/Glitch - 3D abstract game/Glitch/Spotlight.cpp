#include "SpotLight.h"

Spotlight::Spotlight()
	: SceneLighting()
{
	m_position = Vector3(0, 0, 0);
	m_attentuation = Vector3(0.4f, 0.02f, 0);
	m_direction = Vector3(0, 0, 0);
	m_spotPower = 1;
}