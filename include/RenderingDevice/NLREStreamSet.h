#ifndef NLRE_STREAM_SET_
#define NLRE_STREAM_SET_

#include "stdafx.h"

class NLRE_GeomStr
{
public:
	NLRE_GeomStr() : position(0.0f, 0.0f, 0.0f), normal(0.0f, 0.0f, 0.0f), textCoord(0.0f, 0.0f){};

	NLE_FLOAT3 position;
	NLE_FLOAT3 normal;
	NLE_FLOAT2 textCoord;
};

typedef unsigned long NLRE_Index;


#endif