#pragma once

//I need this because the LightBuffer acts weird and gives uses the wrong values in the pixel shader
#define ALIGN_REGISTER _declspec(align(16))

#include "Shader.h"
#include "Spotlight.h"

class FlashlightShader : public Shader
{
protected:
	struct LightBuffer
	{
		ALIGN_REGISTER Color ambientColour;
		ALIGN_REGISTER float ambientIntensity;
		ALIGN_REGISTER Vector4 diffuseDirection;
		ALIGN_REGISTER Color diffuseColour;
		ALIGN_REGISTER float diffuseIntensity;
		ALIGN_REGISTER Vector4 lightPos;
		ALIGN_REGISTER Vector3 lightAtt;
		ALIGN_REGISTER Vector4 lightDirection;
		ALIGN_REGISTER float spotPower;
		Vector2 padding;
	};
	
	Spotlight* m_lightSetup;
	ID3D11SamplerState* m_textureSampler;
	ID3D11Buffer* m_lightBuffer;

public:
	FlashlightShader(Spotlight* spotlight);

	virtual void Begin(ID3D11DeviceContext* context);
	virtual bool Initialise(ID3D11Device* device, LPCWSTR vertexFilename, LPCWSTR pixelFilename);
	virtual bool SetConstants(ID3D11DeviceContext* context, Matrix world, Matrix view, Matrix projection);
	virtual bool SetTexture(ID3D11DeviceContext* context, ID3D11ShaderResourceView* textureView);
	virtual void Release();
};