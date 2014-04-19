#include "stdafx.h"
#include "math\DXMath\DXMathVectorStoreFunctions.h"

inline void NLEStoreFloat3(NLE_FLOAT3* destination, NLE_VECTOR v)
{
	XMStoreFloat3(destination, v);
}

inline void NLEStoreFloat3A(NLE_FLOAT3A* destination, NLE_VECTOR v)
{
	XMStoreFloat3A(destination, v);
}

inline void NLEStoreFloat4(NLE_FLOAT4* destination, NLE_VECTOR v)
{
	XMStoreFloat4(destination, v);
}

inline void NLEStoreFloat4A(NLE_FLOAT4A* destination, NLE_VECTOR v)
{
	XMStoreFloat4A(destination, v);
}

inline void NLEStoreFloat3x3(NLE_FLOAT3X3* destination, NLE_MATRIX v)
{
	XMStoreFloat3x3(destination, v);
}

inline void NLEStoreFloat4x4(NLE_FLOAT4X4* destination, NLE_MATRIX v)
{
	XMStoreFloat4x4(destination, v);
}

inline void NLEStoreFloat4x4A(NLE_FLOAT4X4A* destination, NLE_MATRIX v)
{
	XMStoreFloat4x4A(destination, v);
}