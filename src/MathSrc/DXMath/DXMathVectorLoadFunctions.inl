#ifdef DX_MATH_VECTOR_LOAD_FUNCTIONS_

inline NLE_VECTOR	NLEMath::NLELoadFloat3		(const NLE_FLOAT3* source)
{
	return DirectX::XMLoadFloat3(source);
}

inline NLE_VECTOR	NLEMath::NLELoadFloat3A(const NLE_FLOAT3A* source)
{
	return DirectX::XMLoadFloat3A(source);
}

inline NLE_MATRIX	NLEMath::NLELoadFloat3x3(const NLE_FLOAT3X3* source)
{
	return DirectX::XMLoadFloat3x3(source);
}

inline NLE_VECTOR	NLEMath::NLELoadFloat4(const NLE_FLOAT4* source)
{
	return DirectX::XMLoadFloat4(source);
}

inline NLE_VECTOR	NLEMath::NLELoadFloat4A(const NLE_FLOAT4A* source)
{
	return DirectX::XMLoadFloat4A(source);
}

inline NLE_MATRIX	NLEMath::NLELoadFloat4x4(const NLE_FLOAT4X4* source)
{
	return XMLoadFloat4x4(source);
}

inline NLE_MATRIX	NLEMath::NLELoadFloat4x4A(const NLE_FLOAT4X4A* source)
{
	return DirectX::XMLoadFloat4x4A(source);
}

#endif
