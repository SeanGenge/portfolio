#pragma once

#include <string>
#include "DirectXTK/SimpleMath.h"
#include "SceneLighting.h"

using namespace DirectX::SimpleMath;

class Spotlight : public SceneLighting
{
private:
	Vector3 m_position;
	Vector3 m_direction;
	Vector3 m_attentuation;
	float m_spotPower;

public:
	Spotlight();

	Vector3 getPosition() { return m_position; }
	Vector3 getAttentuation() { return m_attentuation; }
	Vector3 getDirection() { return m_direction; }
	float getSpotPower() { return m_spotPower; }

	void setPosition(Vector3 pos) { m_position = pos; }
	void setAttentuation(Vector3 att) { m_attentuation = att; }
	void setDirection(Vector3 dir) { m_direction = dir; }
	void setSpotPower(float spotP) { m_spotPower = spotP; }
};