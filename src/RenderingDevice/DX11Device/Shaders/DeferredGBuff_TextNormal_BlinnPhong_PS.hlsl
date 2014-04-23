Texture2D DiffuseMap		: register(t0);
Texture2D NormalMap			: register(t1);
SamplerState AnisoSampler	: register(s0);

struct PSInput
{
	float4 PositionSS	: SV_Position;
	float2 TexCoord		: TEXCOORD;
	float3 NormalWS		: NORMALWS;
	float3 PositionWS	: POSITIONWS;
	float3 TangentWS	: TANGENTWS;
	float3 BitangentWS	: BITANGENTWS;
};

struct PSOutput
{
	float4 Normal			: SV_TARGET0;
	float4 DiffuseAlbedo	: SV_TARGET1;
	float4 SpecularAlbedo	: SV_TARGET2;
	float4 Position			: SV_TARGET3;
};

// G-Buffer pixel shader, with normal mapping PSOutput PSMain( in PSInput input )
PSOutput PSMain(in PSInput input)
{
	PSOutput output;
	// Sample the diffuse map
	float3 diffuseAlbedo = DiffuseMap.Sample(AnisoSampler,
		input.TexCoord).rgb;

	// Normalize the tangent frame after interpolation
	float3x3 tangentFrameWS = float3x3(normalize(input.TangentWS),
		normalize(input.BitangentWS), normalize(input.NormalWS))j
		// Sample the tangent-space normal map and decompress
		float3 normalTS = MormalMap.Sample(AnisoSampler, input.TexCoord).rgb;
		normalTS = normalize(normalTS * 2.0f - 1.0f);
	// Convert to world space
	float3 normalWS = mul(normalTS, tangentFrameWS);
		// Output our G-Buffer values
		output.Normal = float4(normalWS, 1.0f);
	output.DiffuseAlbedo = float4(diffuseAlbedo, 1.0f);
	output.SpecularAlbedo = float4(SpecularAlbedo, SpecularPower);
	output.Position = float4(input.PositionWS, 1.0f);
	return output;
}