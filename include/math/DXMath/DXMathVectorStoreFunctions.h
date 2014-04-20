#ifndef DX_MATH_VECTOR_STORE_FUNCTIONS_
#define DX_MATH_VECTOR_STORE_FUNCTIONS_

static void _NLE_CALLCONV_ NLEStoreFloat3(NLE_FLOAT3* destination, NLE_FVECTOR v);
static void _NLE_CALLCONV_ NLEStoreFloat3A(NLE_FLOAT3A* destination, NLE_FVECTOR v);
static void _NLE_CALLCONV_ NLEStoreFloat4(NLE_FLOAT4* destination, NLE_FVECTOR v);
static void _NLE_CALLCONV_ NLEStoreFloat4A(NLE_FLOAT4A* destination, NLE_FVECTOR v);
static void _NLE_CALLCONV_ NLEStoreFloat3x3(NLE_FLOAT3X3* destination, NLE_FMATRIX v);
static void _NLE_CALLCONV_ NLEStoreFloat4x4(NLE_FLOAT4X4* destination, NLE_FMATRIX v);
static void _NLE_CALLCONV_ NLEStoreFloat4x4A(NLE_FLOAT4X4A* destination, NLE_FMATRIX v);

#endif