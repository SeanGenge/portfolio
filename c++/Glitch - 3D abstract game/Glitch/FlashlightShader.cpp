#include "FlashlightShader.h"

FlashlightShader::FlashlightShader(Spotlight* spotlight) : Shader()
{
	m_textureSampler = NULL;
	m_lightSetup = spotlight;
}

bool FlashlightShader::Initialise(ID3D11Device* device, LPCWSTR vertexFilename, LPCWSTR pixelFilename)
{
	D3D11_SAMPLER_DESC textureSamplerDescription;	//When we create a sampler we need a Description struct to describe how we want to create the sampler

	if (!Shader::Initialise(device, vertexFilename, pixelFilename))		//We'll use the parent method to create most of the shader
	{
		return false;
	}

	//Now all we need to do is fill out our sampler description
	textureSamplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		//This is the Filtering method used for the texture... 
	//...different values will give you different quality texture output
	textureSamplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//This defines what happens when we sample outside of the range [0...1]
	textureSamplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;		//In our case we just want it to wrap around so that we always are sampling something
	textureSamplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	textureSamplerDescription.MipLODBias = 0.0f;							//The rest of these values are really just "Defaults"
	textureSamplerDescription.MaxAnisotropy = 1;							//If you want more info look up D3D11_SAMPLER_DESC on MSDN
	textureSamplerDescription.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	textureSamplerDescription.BorderColor[0] = 1;
	textureSamplerDescription.BorderColor[1] = 1;
	textureSamplerDescription.BorderColor[2] = 1;
	textureSamplerDescription.BorderColor[3] = 1;
	textureSamplerDescription.MinLOD = 0;
	textureSamplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

	//and create the sampler!
	if (FAILED(device->CreateSamplerState(&textureSamplerDescription, &m_textureSampler)))
	{
		return false;
	}

	//Create the light buffer
	D3D11_BUFFER_DESC lightBufferDescription;
	lightBufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDescription.ByteWidth = sizeof(LightBuffer);
	lightBufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDescription.MiscFlags = 0;
	lightBufferDescription.StructureByteStride = 0;

	if (FAILED(device->CreateBuffer(&lightBufferDescription, NULL, &m_lightBuffer)))
	{
		return false;
	}

	return true;
}

void FlashlightShader::Begin(ID3D11DeviceContext* context)
{
	Shader::Begin(context);		//Let the parent class do most of the work!

	context->PSSetSamplers(0, 1, &m_textureSampler);
	context->PSSetConstantBuffers(0, 1, &m_lightBuffer);
}

bool FlashlightShader::SetConstants(ID3D11DeviceContext* context, Matrix world, Matrix view, Matrix projection)
{
	if (!Shader::SetConstants(context, world, view, projection))
	{
		return false;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	LightBuffer* inputData;

	if (FAILED(context->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		return false;
	}

	inputData = (LightBuffer*)mappedResource.pData;

	inputData->ambientColour = m_lightSetup->getAmbientColour();
	inputData->ambientIntensity = m_lightSetup->getAmbientIntensity();

	inputData->diffuseDirection = Vector4(m_lightSetup->getDiffuseDirection().x, m_lightSetup->getDiffuseDirection().y, m_lightSetup->getDiffuseDirection().z, 1.0f);
	inputData->diffuseColour = m_lightSetup->getDiffuseColour();
	inputData->diffuseIntensity = m_lightSetup->getDiffuseIntensity();

	inputData->lightPos = Vector4(m_lightSetup->getPosition().x, m_lightSetup->getPosition().y, m_lightSetup->getPosition().z, 1.0f);
	inputData->lightDirection = Vector4(m_lightSetup->getDirection().x, m_lightSetup->getDirection().y, m_lightSetup->getDirection().z, 1.0f);
	inputData->lightAtt = m_lightSetup->getAttentuation();
	inputData->spotPower = m_lightSetup->getSpotPower();

	context->Unmap(m_lightBuffer, 0);

	return true;
}

bool FlashlightShader::SetTexture(ID3D11DeviceContext* context, ID3D11ShaderResourceView* textureView)
{
	//This shader does have a texture so it does something in this method!
	context->PSSetShaderResources(0, 1, &textureView);
	return true;
}

void FlashlightShader::Release()
{
	Shader::Release();
	if (m_textureSampler)
	{
		m_textureSampler->Release();
		m_textureSampler = NULL;
	}

	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = NULL;
	}
}