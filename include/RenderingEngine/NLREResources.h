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
#ifndef NLRE_RESOURCES_
#define NLRE_RESOURCES_

#include "NLEConfigurator.h"
#include "Math\NLEMath.h"

#ifdef _DX11_
	#include "RenderingEngine\RenderingDevice\DX11Device\NLREDX11ResourceWrap.h"
#endif
#include <memory>

enum NLRE_RENDERING_TECHNIQUE_ID
{
	NLRE_FORWARD_RT
};

enum NLRE_SHADING_MODEL
{
	NLRE_SHADING_MODEL_FLAT,
	NLRE_SHADING_MODEL_GOURAUD,
	NLRE_SHADING_MODEL_PHONG,
	NLRE_SHADING_MODEL_BLINN,
	NLRE_SHADING_MODEL_TOON,
	NLRE_SHADING_MODEL_OREN_NAYAR,
	NLRE_SHADING_MODEL_MINNAERT,
	NLRE_SHADING_MODEL_COOK_TORRANCE,
	NLRE_SHADING_MODEL_NO_SHADING,
	NLRE_SHADING_MODEL_FRESNEL
};

enum NLRE_BLENDING_MODE
{
	NLRE_BLENDING_MODE_DEFAULT,
	NLRE_BLENDING_MODE_ADDITIVE,
	NLRE_BLENDING_MODE_NONE
};

struct NLRE_Buffer
{
	NLRE_Buffer() : apiBuffer(NULL),
		usage(NLRE_USAGE::NLRE_USAGE_DEFAULT),
		elementSize(0), numberElements(0){}
	~NLRE_Buffer()
	{ 
		if (apiBuffer)
		{
			apiBuffer->Release();
			apiBuffer = NULL;
		}
	}

	NLRE_APIBuffer* apiBuffer;
	NLRE_BIND_FLAG bindFlag;
	NLRE_USAGE usage;
	unsigned int elementSize;
	unsigned int numberElements;
};

struct NLRE_VertexShader
{
	NLRE_VertexShader() : apiVertexShader(NULL), blob(NULL){}
	~NLRE_VertexShader()
	{ 
		if (apiVertexShader)
		{
			apiVertexShader->Release();
			apiVertexShader = NULL;
		}
		if (blob)
		{
			blob->Release();
			blob = NULL;
		}
	}
	NLRE_APIVertexShader* apiVertexShader;
	NLRE_ShaderBlob* blob;
};

struct NLRE_PixelShader
{
	NLRE_PixelShader() : apiPixelShader(NULL), blob(NULL) {}
	~NLRE_PixelShader()
	{ 
		if (apiPixelShader)
		{
			apiPixelShader->Release();
			apiPixelShader = NULL;
		}
		if (blob)
		{
			blob->Release();
			blob = NULL;
		}
	}
	NLRE_APIPixelShader* apiPixelShader;
	NLRE_ShaderBlob* blob;
};

struct NLRE_InputLayoutDesc
{
	NLRE_InputLayoutDesc(const NLRE_APIInputLayoutDecs* apiInputLayoutDesc, const size_t numberElements) 
		: apiInputLayoutDesc(apiInputLayoutDesc), numberElements(numberElements){}
	const NLRE_APIInputLayoutDecs* apiInputLayoutDesc;
	const size_t numberElements;
};

struct NLRE_Mesh
{
	NLRE_Buffer geomBuffer;
	NLRE_Buffer indexBuffer;
};

__declspec(align(16)) 
struct NLRE_MaterialBufferStruct
{
	NLRE_MaterialBufferStruct() :
		diffuseColor(NLE_FLOAT3(1.0f, 0.0f, 1.0f)),
		ambientColor(NLE_FLOAT3(1.0f, 0.0f, 1.0f)),
		specularColor(NLE_FLOAT3(1.0f, 0.0f, 1.0f)),
		emissiveColor(NLE_FLOAT3(1.0f, 0.0f, 1.0f)),
		transparentColor(NLE_FLOAT3(1.0f, 0.0f, 1.0f)),
		opacity(1.0f),
		shininess(0.0f),
		shininess_str(0.0f),
		refracti(0.0f){};

	NLE_FLOAT3 diffuseColor;
	NLE_FLOAT3 ambientColor;
	NLE_FLOAT3 specularColor;
	NLE_FLOAT3 emissiveColor;
	NLE_FLOAT3 transparentColor;	
	
	float opacity;
	float shininess;
	float shininess_str;
	float refracti;
};

struct NLRE_Material
{
	NLRE_Material() :
		wireframe(false),
		twoSided(false),
		blendMode(NLRE_BLENDING_MODE_NONE),
		shadingModel(NLRE_SHADING_MODEL_PHONG),
		textureMappingMode_u(NLRE_TEXTURE_MAP_MODE_WRAP),
		textureMappingMode_v(NLRE_TEXTURE_MAP_MODE_WRAP),

		diffuseText(NULL),
		specularText(NULL),
		ambientText(NULL),
		emissiveText(NULL),
		heightmapText(NULL),
		normalText(NULL),
		shininessText(NULL),
		opacityText(NULL),
		displacementText(NULL),
		lightmapText(NULL),
		reflectionText(NULL),

		diffuseTextView(NULL),
		specularTextView(NULL),
		ambientTextView(NULL),
		emissiveTextView(NULL),
		heightmapTextView(NULL),
		normalTextView(NULL),
		shininessTextView(NULL),
		opacityTextView(NULL),
		displacementTextView(NULL),
		lightmapTextView(NULL),
		reflectionTextView(NULL){};

	~NLRE_Material()
	{
		if (diffuseText) diffuseText->Release();
		diffuseText = NULL;
		if (specularText) specularText->Release();
		specularText = NULL;
		if (ambientText) ambientText->Release();
		ambientText = NULL;
		if (emissiveText) emissiveText->Release();
		emissiveText = NULL;
		if (heightmapText) heightmapText->Release();
		heightmapText = NULL;
		if (normalText) normalText->Release();
		normalText = NULL;
		if (shininessText) shininessText->Release();
		shininessText = NULL;
		if (opacityText) opacityText->Release();
		opacityText = NULL;
		if (displacementText) displacementText->Release();
		displacementText = NULL;
		if (lightmapText) lightmapText->Release();
		lightmapText = NULL;
		if (reflectionText) reflectionText->Release();
		reflectionText = NULL;

		if (diffuseTextView) diffuseTextView->Release();
		diffuseTextView = NULL;
		if (specularTextView) specularTextView->Release();
		specularTextView = NULL;
		if (ambientTextView) ambientTextView->Release();
		ambientTextView = NULL;
		if (emissiveTextView) emissiveTextView->Release();
		emissiveTextView = NULL;
		if (heightmapTextView) heightmapTextView->Release();
		heightmapTextView = NULL;
		if (normalTextView) normalTextView->Release();
		normalTextView = NULL;
		if (shininessTextView) shininessTextView->Release();
		shininessTextView = NULL;
		if (opacityTextView) opacityTextView->Release();
		opacityTextView = NULL;
		if (displacementTextView) displacementTextView->Release();
		displacementTextView = NULL;
		if (lightmapTextView) lightmapTextView->Release();
		lightmapTextView = NULL;
		if (reflectionTextView) reflectionTextView->Release();
		reflectionTextView = NULL;
	}

	NLRE_Buffer materialBuffer;

	bool wireframe;
	bool twoSided;
	int blendMode;	//0 = Default:    SourceColor*SourceAlpha + DestColor*(1-SourceAlpha),   1 = Additive:  SourceColor*1 + DestColor*1
	int shadingModel;
	int textureMappingMode_u;
	int textureMappingMode_v;

	NLRE_APITexture2D* diffuseText;
	NLRE_APITexture2D* specularText;
	NLRE_APITexture2D* ambientText;
	NLRE_APITexture2D* emissiveText;
	NLRE_APITexture2D* heightmapText;
	NLRE_APITexture2D* normalText;
	NLRE_APITexture2D* shininessText;
	NLRE_APITexture2D* opacityText;
	NLRE_APITexture2D* displacementText;
	NLRE_APITexture2D* lightmapText;
	NLRE_APITexture2D* reflectionText;

	NLRE_APIShaderResourceView* diffuseTextView;
	NLRE_APIShaderResourceView* specularTextView;
	NLRE_APIShaderResourceView* ambientTextView;
	NLRE_APIShaderResourceView* emissiveTextView;
	NLRE_APIShaderResourceView* heightmapTextView;
	NLRE_APIShaderResourceView* normalTextView;
	NLRE_APIShaderResourceView* shininessTextView;
	NLRE_APIShaderResourceView* opacityTextView;
	NLRE_APIShaderResourceView* displacementTextView;
	NLRE_APIShaderResourceView* lightmapTextView;
	NLRE_APIShaderResourceView* reflectionTextView;
};

struct NLRE_Transformation
{
	NLE_FLOAT4X4 transformation;
};

struct NLRE_RenderableAsset
{
	NLRE_RenderableAsset() : mesh(NULL), material(NULL){};

	NLRE_Transformation transformStruct;
	NLRE_Buffer transformationBuffer;
	std::shared_ptr<NLRE_Mesh> mesh;
	std::shared_ptr<NLRE_Material> material;
};



#endif