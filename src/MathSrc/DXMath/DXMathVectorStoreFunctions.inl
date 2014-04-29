#ifdef DX_MATH_VECTOR_STORE_FUNCTIONS_

inline void _NLE_CALLCONV_ NLEMath::NLEStoreFloat3(NLE_FLOAT3* destination,  NLE_FVECTOR v)
{
	DirectX::XMStoreFloat3(destination, v);
}

inline void _NLE_CALLCONV_ NLEMath::NLEStoreFloat3A(NLE_FLOAT3A* destination,  NLE_FVECTOR v)
{
	DirectX::XMStoreFloat3A(destination, v);
}

inline void _NLE_CALLCONV_ NLEMath::NLEStoreFloat4(NLE_FLOAT4* destination,  NLE_FVECTOR v)
{
	DirectX::XMStoreFloat4(destination, v);
}

inline void _NLE_CALLCONV_ NLEMath::NLEStoreFloat4A(NLE_FLOAT4A* destination,  NLE_FVECTOR v)
{
	DirectX::XMStoreFloat4A(destination, v);
}

inline void _NLE_CALLCONV_ NLEMath::NLEStoreFloat3x3(NLE_FLOAT3X3* destination,  NLE_FMATRIX v)
{
	DirectX::XMStoreFloat3x3(destination, v);
}

inline void _NLE_CALLCONV_ NLEMath::NLEStoreFloat4x4(NLE_FLOAT4X4* destination,  NLE_FMATRIX v)
{
	DirectX::XMStoreFloat4x4(destination, v);
}

inline void _NLE_CALLCONV_ NLEMath::NLEStoreFloat4x4A(NLE_FLOAT4X4A* destination,  NLE_FMATRIX v)
{
	DirectX::XMStoreFloat4x4A(destination, v);
}

#endif