/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 NonLinear Rendering Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

Texture2D DiffuseMap		: register(t0);
Texture2D NormalMap			: register(t1);
SamplerState AnisoSampler	: register(s0);

cbuffer MatProperties
{
	float3 SpecularAlbedo;
	float SpecularPower;
};

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
		normalize(input.BitangentWS), normalize(input.NormalWS));
	// Sample the tangent-space normal map and decompress
	float3 normalTS = NormalMap.Sample(AnisoSampler, input.TexCoord).rgb;
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