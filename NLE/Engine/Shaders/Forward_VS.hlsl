/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

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

cbuffer cbTransformation : register(b0)
{
	float4x4 world;
	float4x4 worldInverseTranspose;
	float4x4 WVP;
};

struct VS_INPUT
{
	float3 Pos : POSITION;
	float3 Normal: NORMAL;
	float2 TexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 PosW : POSITION; 
	float3 NormalW : NORMAL;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VSMain(in VS_INPUT input)
{
	VS_OUTPUT output;
	// Transform to world space space. 
	output.PosW = mul(float4(input.Pos, 1.0f), world).xyz;
	output.NormalW = mul(input.Normal, (float3x3)worldInverseTranspose);

	output.Pos = mul(float4(input.Pos, 1.0f), WVP);
	output.TexCoord = input.TexCoord;

	return output;
}
