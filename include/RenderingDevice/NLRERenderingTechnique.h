#ifndef NLRE_RENDERING_TECHNIQUE_
#define NLRE_RENDERING_TECHNIQUE_

#include "NLREMain\stdafx.h"
class NLRERenderingTechnique
{
public:
	virtual void render(NLRE_Buffer vertexBuff, NLRE_Buffer indexBuff, NLRE_Buffer constBuff, NLRE_APIShaderResourceView* texture) = 0;
};

#endif