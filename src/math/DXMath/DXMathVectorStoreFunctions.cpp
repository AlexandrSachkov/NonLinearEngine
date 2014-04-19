#include "stdafx.h"
#include "math\DXMath\DXMathVectorStoreFunctions.h"

inline void NLEStoreFloat3(NLE_FLOAT3* destination, const NLE_VECTOR& v)
{
	DirectX::XMStoreFloat3(destination, v);
}

inline void NLEStoreFloat3A(NLE_FLOAT3A* destination, const NLE_VECTOR& v)
{
	DirectX::XMStoreFloat3A(destination, v);
}

inline void NLEStoreFloat4(NLE_FLOAT4* destination, const NLE_VECTOR& v)
{
	DirectX::XMStoreFloat4(destination, v);
}

inline void NLEStoreFloat4A(NLE_FLOAT4A* destination, const NLE_VECTOR& v)
{
	DirectX::XMStoreFloat4A(destination, v);
}

inline void NLEStoreFloat3x3(NLE_FLOAT3X3* destination, const NLE_MATRIX& v)
{
	DirectX::XMStoreFloat3x3(destination, v);
}

inline void NLEStoreFloat4x4(NLE_FLOAT4X4* destination, const NLE_MATRIX& v)
{
	DirectX::XMStoreFloat4x4(destination, v);
}

inline void NLEStoreFloat4x4A(NLE_FLOAT4X4A* destination, const NLE_MATRIX& v)
{
	DirectX::XMStoreFloat4x4A(destination, v);
}