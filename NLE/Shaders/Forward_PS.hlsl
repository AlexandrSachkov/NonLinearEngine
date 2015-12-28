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

struct DirectionalLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Direction;
	float pad;
};
struct PointLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Position;
	float Range;
	float3 Att;
	float pad;
};
struct SpotLight
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float3 Position;
	float Range;
	float3 Direction;
	float Spot;
	float3 Att;
	float pad;
};

struct Material
{
	float4 Diffuse;
	float4 Ambient;
	float4 Specular;
	float4 Emissive;
	float4 Transparent;

	float opacity;
	float shininess;
	float shininess_str;
	float refracti;
};

cbuffer cbLights : register(b0)
{
	DirectionalLight directionalLights[32];
	PointLight pointLights[32];
	SpotLight spotLights[32];
	uint numDirLights;
	uint numPointLights;
	uint numSpotLights;
};

cbuffer cbMaterial : register(b1)
{
	Material material;
};

cbuffer cbEye : register(b2)
{
	float3 eyePosW;
}



struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormalW : NORMAL;
	float2 TexCoord : TEXCOORD;
};

Texture2D ObjTexture : register(t0);
SamplerState ObjSamplerState : register(s0);

void ComputePointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 spec)
{
	// Initialize outputs. 
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f); 
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f); 
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The vector from the surface to the light. 
	float3 lightVec = L.Position - pos; 
	// The distance from surface to light. 
	float d = length(lightVec); 
	// Range test. 
	if(d > L.Range) return; 
	// Normalize the light vector. 
	lightVec /= d; 
	// Ambient term. 
	ambient = mat.Ambient * L.Ambient; 
	// Add diffuse and specular term, provided the surface is in the line of site of the light. 
	float diffuseFactor = dot(lightVec, normal); 
	// Flatten to avoid dynamic branching. 
	[flatten] 
	if(diffuseFactor > 0.0f) 
	{ 
		float3 v = reflect(-lightVec, normal); 
		float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w); 
		diffuse = diffuseFactor * mat.Diffuse * L.Diffuse; 
		spec = specFactor * mat.Specular * L.Specular; 
	} 
	// Attenuate 
	float att = 1.0f / dot(L.Att, float3(1.0f, d, d*d)); 
	diffuse *= att; 
	spec    *= att;

}

float4 PSMain(PS_INPUT input) : SV_TARGET
{
	// Interpolating normal can unnormalize it, so normalize it.
	input.NormalW = normalize(input.NormalW);
	float3 toEyeW = normalize(eyePosW - input.PosW);

	// Start with a sum of zero. 
	float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f); 
	float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f); 
	float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f); 

	// Sum the light contribution from each light source. 
	float4 A, D, S;

	[unroll]
	for (uint i = 0; i < numPointLights; i++)
	{
		ComputePointLight(material, pointLights[i], input.PosW, input.NormalW, toEyeW, A, D, S);
		ambient += A; 
		diffuse += D; 
		spec += S;
	}

	float4 texColor = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
	
	float4 litColor = texColor*(ambient + diffuse) + spec; 
	// Common to take alpha from diffuse material. 
	litColor.a = material.Diffuse.a; 

	return litColor;
}