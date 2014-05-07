#ifndef NLRE_RESOURCES_
#define NLRE_RESOURCES_

#ifdef _DX11_
	#include "RenderingDevice\DX11Device\NLREDX11ResourceWrap.h"
#endif

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

struct NLRE_MaterialBufferStruct
{
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
	NLRE_Buffer materialBuffer;

	bool wireframe;
	bool twoSided;
	int blendMode;	//true = Default:    SourceColor*SourceAlpha + DestColor*(1-SourceAlpha),   false = Additive:  SourceColor*1 + DestColor*1
	int shadingModel;
	int textureMappingMode_u;
	int textureMappingMode_v;
};

struct NLRE_RenderableAsset
{
	NLRE_Mesh* mesh;
	NLRE_Material* material;
};

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

#endif