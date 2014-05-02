#ifndef NLRE_TEXTURE_LOADER_
#define NLRE_TEXTURE_LOADER_

#include "NLREMain\stdafx.h"

class NLRETextureLoader
{
public:
	virtual bool loadTexture2D(std::wstring path, NLRE_APITexture2D*& texture2D, NLRE_APIShaderResourceView*& resourceView) =0;
};
#endif