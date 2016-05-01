#include "SceneLighting.h"

SceneLighting::SceneLighting()
{
	m_ambientColour = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_ambientIntensity = 1.0f;

	m_diffuseDirection = Vector3(0, 0, 0);
	m_diffuseColour = Color(1.0f, 1.0f, 1.0f, 1.0f);
	m_diffuseIntensity = 1.0f;
}