#ifndef NLRE_RESOURCES_
#define NLRE_RESOURCES_

#ifdef _DX11_
	#include "RenderingDevice\DX11Device\NLREDX11ResourceWrap.h"
#endif

struct NLRE_Buffer
{
	NLRE_Buffer() : apiBuffer(NULL),
		usage(NLRE_USAGE::NLRE_USAGE_DEFAULT),
		elementSize(0){}
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

enum NLRE_RENDERING_TECHNIQUE_ID
{
	NLRE_FORWARD_RT
};

#endif