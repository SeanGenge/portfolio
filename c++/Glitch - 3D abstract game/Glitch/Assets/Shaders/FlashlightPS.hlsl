Texture2D meshTexture;
SamplerState samplerType;

//Helped get a spot light to work (Post #15)- http://www.gamedev.net/topic/637215-adding-attenuation-to-hlsl-point-light/
//I could not do a flashlight so I decided to just do a spotlight.
//Both spotlight effects work so you can comment the other one and try the other one if you want. they both look different

cbuffer LightingBuffer
{
    float4 ambientColour;
    float ambientIntensity;
    float4 diffuseDirection;
    float4 diffuseColour;
    float diffuseIntensity;
    float4 lightPos;
    float3 lightAtt;
    float4 lightDirection;
    float spotPower;
    float2 padding;
};

struct PixelInput
{
    float4 position : SV_POSITION;
	float4 colour : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
    float4 worldPos : TEXCOORD1;
};

//float4 main(PixelInput input) : SV_TARGET
//{
//    //This is one version of a spotlight. I liked the second one better
//    float4 finalColour = float4(0.0f, 0.0f, 0.0f, 1.0f);

//    //Texture colour
//    float4 textureColour = meshTexture.Sample(samplerType, input.uv);

//    //Ambient light
//    float ambientLight = ambientColour.rgb * ambientIntensity;

//    //Diffuse light - Does not work with attentuation
//    float dLightIntensity = max(dot(input.normal, diffuseDirection), 0);
//    float diffuseLight = saturate(diffuseColour.rgb * dLightIntensity * diffuseIntensity);

//    //Attentuation factor
//    float d = distance(lightPos, input.worldPos);
//    float a = lightAtt.x + lightAtt.y * d + lightAtt.z * d * d;

//    //Flashlight - Does not work. Got this from online and found it in a book
//    float lightV = normalize(lightPos - input.worldPos);
//    float spot = pow(max(dot(-lightV, lightDirection), 0), spotPower);
    
//    //The final colour of the pixel
//    finalColour = ambientLight + (input.colour * textureColour) / a;

//    return saturate(finalColour);
//}

float4 main(PixelInput input) : SV_TARGET
{
    //The secone version of a spotlight. A lot of the LightingBuffer is not used. Was used on the first spotlight but I prefer this effect
    //Spotlight
    float4 finalColour = float4(0.0f, 0.0f, 0.0f, 1.0f);
    float4 textureColour = meshTexture.Sample(samplerType, input.uv);

    float dist = distance(lightPos, input.worldPos);

    //Set the range of the light
    float att = 1.0f - saturate(dist / 60);

    finalColour = (input.colour * textureColour * att);

    return saturate(finalColour);
}