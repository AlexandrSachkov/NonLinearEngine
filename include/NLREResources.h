#ifndef NLRE_RESOURCES_
#define NLRE_RESOURCES_

#include "RenderingDevice\NLRERenderStateID.h"

#ifdef _DX11_
	#include "RenderingDevice\DX11Device\NLREDX11ResourceWrap.h"
#endif

struct NLRE_Buffer
{
	NLRE_Buffer() : apiBuffer(NULL),
		usage(NLRE_USAGE::NLRE_USAGE_DEFAULT),
		elementSize(0){}
	~NLRE_Buffer(){ apiBuffer->Release(); }

	NLRE_APIBuffer* apiBuffer;
	NLRE_BIND_FLAG bindFlag;
	NLRE_USAGE usage;
	unsigned int elementSize;
};

struct NLRE_ShaderBlob
{
	NLRE_ShaderBlob() : data(NULL), size(0){}
	~NLRE_ShaderBlob(){ delete data; }
	void* data;
	size_t size;
};

struct NLRE_VertexShader
{
	NLRE_VertexShader() : apiVertexShader(NULL){}
	~NLRE_VertexShader(){ delete apiVertexShader; }
	NLRE_APIVertexShader* apiVertexShader;
	NLRE_ShaderBlob blob;
};

struct NLRE_PixelShader
{
	NLRE_PixelShader() : apiPixelShader(NULL){}
	~NLRE_PixelShader(){ delete apiPixelShader; }
	NLRE_APIPixelShader* apiPixelShader;
	NLRE_ShaderBlob blob;
};

struct NLRE_InputLayoutDesc
{
	NLRE_InputLayoutDesc(const NLRE_APIInputLayoutDecs* apiInputLayoutDesc, const size_t numberElements) 
		: apiInputLayoutDesc(apiInputLayoutDesc), numberElements(numberElements){}
	const NLRE_APIInputLayoutDecs* apiInputLayoutDesc;
	const size_t numberElements;
};

#endif