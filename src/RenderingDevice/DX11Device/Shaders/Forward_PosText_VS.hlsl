cbuffer cbPerObject
{
	float4x4 WVP;
};

struct VS_INPUT
{
	float4 inPos : POSITION;
	float2 inTexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VSMain(in VS_INPUT input)
{
	VS_OUTPUT output;

	output.Pos = mul(input.inPos, WVP);
	output.TexCoord = input.inTexCoord;

	return output;
}
