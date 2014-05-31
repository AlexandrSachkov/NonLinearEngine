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

cbuffer Transform	: register(b0)
{
	matrix WorldMatrix;
	matrix WorldViewMatrix;
	matrix WorldViewProjMatrix;
};

struct VSInput
{
	float4 Position : POSITION;
	float3 Normal	: NORMAL;
	float4 Tangent	: TANGENT;
	float2 TexCoord : TEXCOORDS0;
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