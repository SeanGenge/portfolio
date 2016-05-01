#ifndef SCENELIGHTING_H
#define SCENELIGHTING_H

#include "DirectXTK/SimpleMath.h"

using namespace DirectX::SimpleMath;

class SceneLighting
{
protected:
	//Ambient light
	Color m_ambientColour;
	float m_ambientIntensity;

	//Diffuse light
	Vector3 m_diffuseDirection;
	Color m_diffuseColour;
	float m_diffuseIntensity;

public:
	SceneLighting();

	Color getAmbientColour() { return m_ambientColour; }
	float getAmbientIntensity() { return m_ambientIntensity; }

	Vector3 getDiffuseDirection() { return m_diffuseDirection; }
	Color getDiffuseColour() { return m_diffuseColour; }
	float getDiffuseIntensity() { return m_diffuseIntensity; }

	void setAmbientColour(Color ambientColour) { m_ambientColour = ambientColour; }
	void setAmbientIntensity(float ambientIntensity) { m_ambientIntensity = ambientIntensity; }

	void setDiffuseDirection(Vector3 diffuseDirection){ m_diffuseDirection = diffuseDirection; }
	void setDiffuseColour(Color diffuseColour) { m_diffuseColour = diffuseColour; }
	void setDiffuseIntensity(float diffuseIntensity) { m_diffuseIntensity = diffuseIntensity; }
};

#endif