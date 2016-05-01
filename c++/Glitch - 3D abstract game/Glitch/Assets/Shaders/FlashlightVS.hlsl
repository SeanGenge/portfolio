cbuffer MatrixBuffer
{
	matrix world;
	matrix view;
	matrix projection;
};

struct VertexInput
{
	float4 position : POSITION;
	float4 colour : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct PixelInput
{
	float4 position : SV_POSITION;
	float4 colour : COLOR;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
    float4 worldPos : TEXCOORD1;
};

PixelInput main(VertexInput input)
{
	PixelInput output;
	input.position.w = 1.0f;

	float4 worldPosition = mul(input.position, world);

	float4 position = mul(worldPosition, view);
	position = mul(position, projection);

    output.colour = input.colour;
	output.position = position;
	output.normal = normalize(mul(input.normal, (float3x3)world));
	output.uv = input.uv;
    output.worldPos = worldPosition;

	return output;
}