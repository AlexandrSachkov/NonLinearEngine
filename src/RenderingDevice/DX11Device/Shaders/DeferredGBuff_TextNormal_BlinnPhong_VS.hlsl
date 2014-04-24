cbuffer Transform	: register(b0)
{
	matrix WorldMatrix;
	matrix WorldViewMatrix;
	matrix WorldViewProjMatrix;
};

struct VSInput
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORDS0;
	float3 Normal	: NORMAL;
	float4 Tangent	: TANGENT;
};

struct VSOutput
{
	float4 PositionCS	: SV_Position;
	float2 TexCoord		: TEXCOORD;
	float3 NormalWS		: NORMALWS;
	float3 PositionWS	: POSITIONWS;
	float3 TangentWS	: TANGENTWS;
	float3 BitangentWS	: BITANGENTWS;
};

// G-Buffer vertex shader, with normal mapping VSOutput VSMain( in VSInput input )
VSOutput VSMain(in VSInput input)
{
	VSOutput output;
	// Convert position and normals to world space
	output.PositionWS = mul(input.Position, WorldMatrix).xyz;
	float3 normalWS = normalize(mul(input.Normal, (float3x3)WorldMatrix));
		output.NormalWS = normalWS;
	// Reconstruct the rest of the tangent frame
	float3 tangentWS = normalize(mul(input.Tangent.xyz,
		(float3x3)WorldMatrix)); float3 bitangentWS = normalize(cross(normalWS, tangentWS))
		* input.Tangent.w;
	output.TangentWS = tangentWS; output.BitangentWS = bitangentWS;
	// Calculate the clip-space position
	output.PositionCS = mul(input.Position, WorldViewProjMatrix);
	// Pass along the texture coordinate
	output.TexCoord = input.TexCoord;
	return output; 
}