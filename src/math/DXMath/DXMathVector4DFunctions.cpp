#include "stdafx.h"
#include "math\DXMath\DXMathVector4DFunctions.h"

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4AngleBetweenNormals(const NLE_VECTOR& n1, const NLE_VECTOR& n2)
{
	return DirectX::XMVector4AngleBetweenNormals(n1, n2);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4AngleBetweenNormalsEst(const NLE_VECTOR& n1, const NLE_VECTOR& n2)
{
	return DirectX::XMVector4AngleBetweenNormalsEst(n1, n2);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4AngleBetweenVectorsconst(const NLE_VECTOR& n1, const NLE_VECTOR& n2)
{
	return DirectX::XMVector4AngleBetweenVectors(n1, n2);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4ClampLength(const NLE_VECTOR& v, float lengthMin, float lengthMax)
{
	return DirectX::XMVector4ClampLength(v, lengthMin, lengthMax);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4ClampLengthV(const NLE_VECTOR& v, const NLE_VECTOR& lengthMin, const NLE_VECTOR& lengthMax)
{
	return DirectX::XMVector4ClampLengthV(v, lengthMin, lengthMax);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Cross(const NLE_VECTOR& v1, const NLE_VECTOR& v2, const NLE_VECTOR& v3)
{
	return DirectX::XMVector4Cross(v1, v2, v3);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Dot(const NLE_VECTOR& v1, const NLE_VECTOR& v2)
{
	return DirectX::XMVector4Dot(v1, v2);
}

inline bool			_NLE_CALLCONV_	NLEVector4InBounds(const NLE_VECTOR& v, const NLE_VECTOR& bounds)
{
	return DirectX::XMVector4InBounds(v, bounds);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Length(const NLE_VECTOR& v)
{
	return DirectX::XMVector4Length(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4LengthEst(const NLE_VECTOR& v)
{
	return DirectX::XMVector4LengthEst(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4LengthSq(const NLE_VECTOR& v)
{
	return DirectX::XMVector4LengthSq(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Normalize(const NLE_VECTOR& v)
{
	return DirectX::XMVector4Normalize(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Orthogonal(const NLE_VECTOR& v)
{
	return DirectX::XMVector4Orthogonal(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4ReciprocalLength(const NLE_VECTOR& v)
{
	return DirectX::XMVector4ReciprocalLength(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4ReciprocalLengthEst(const NLE_VECTOR& v)
{
	return DirectX::XMVector4ReciprocalLengthEst(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Reflect(const NLE_VECTOR& incident, const NLE_VECTOR& normal)
{
	return DirectX::XMVector4Reflect(incident, normal);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Refract(const NLE_VECTOR& incident, const NLE_VECTOR& normal, float refractionIndex)
{
	return DirectX::XMVector4Refract(incident, normal, refractionIndex);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4RefractV(const NLE_VECTOR& incident, const NLE_VECTOR& normal, const NLE_VECTOR& refractionIndex)
{
	return DirectX::XMVector4RefractV(incident, normal, refractionIndex);
}




inline NLE_VECTOR	_NLE_CALLCONV_ NLEVectorSet(float x, float y, float z, float w)
{
	return NLEVectorSet(x, y, z, w);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEVector4Transform(const NLE_VECTOR& v, const NLE_MATRIX& m)
{
	return DirectX::XMVector4Transform(v, m);
}

inline NLE_FLOAT4*	_NLE_CALLCONV_	NLEVector4TransformStream(NLE_FLOAT4* outputStream, size_t outputStride,
	const NLE_FLOAT4* inputStream, size_t inputStride,
	size_t vectorCount, const NLE_MATRIX& m)
{
	return DirectX::XMVector4TransformStream(outputStream, outputStride, inputStream, inputStride, vectorCount, m);
}

inline NLE_VECTOR	NLEVectorZero()
{
	return DirectX::XMVectorZero();
}