#include "stdafx.h"
#include "math\DXMath\DXMathVectorLoadFunctions.h"

inline NLE_VECTOR	NLELoadFloat3		(const NLE_FLOAT3* source)
{
	return XMLoadFloat3(source);
}

inline NLE_VECTOR	NLELoadFloat3A		(const NLE_FLOAT3A* source)
{
	return XMLoadFloat3A(source);
}

inline NLE_MATRIX	NLELoadFloat3x3		(const NLE_FLOAT3X3* source)
{
	return XMLoadFloat3x3(source);
}

inline NLE_VECTOR	NLELoadFloat4(const NLE_FLOAT4* source)
{
	return XMLoadFloat4(source);
}

inline NLE_VECTOR	NLELoadFloat4A(const NLE_FLOAT4A* source)
{
	return XMLoadFloat4A(source);
}

inline NLE_MATRIX	NLELoadFloat4x4(const NLE_FLOAT4X4* source)
{
	return XMLoadFloat4x4(source);
}

inline NLE_MATRIX	NLELoadFloat4x4A(const NLE_FLOAT4X4A* source)
{
	return XMLoadFloat4x4A(source);
}
