#ifndef DX_MATH_VECTOR_LOAD_FUNCTIONS_
#define DX_MATH_VECTOR_LOAD_FUNCTIONS_

namespace NLEMath
{
	NLE_VECTOR	NLELoadFloat3(const NLE_FLOAT3* source);
	NLE_VECTOR	NLELoadFloat3A(const NLE_FLOAT3A* source);
	NLE_MATRIX	NLELoadFloat3x3(const NLE_FLOAT3X3* source);
	NLE_VECTOR	NLELoadFloat4(const NLE_FLOAT4* source);
	NLE_VECTOR	NLELoadFloat4A(const NLE_FLOAT4A* source);
	NLE_MATRIX	NLELoadFloat4x4(const NLE_FLOAT4X4* source);
	NLE_MATRIX	NLELoadFloat4x4A(const NLE_FLOAT4X4A* source);
}
#include "MathSrc\DXMath\DXMathVectorLoadFunctions.inl"

#endif