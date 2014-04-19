#include "stdafx.h"
#include "math\DXMath\DXMathVector4DFunctions.h"

inline NLE_VECTOR	NLEVector4AngleBetweenNormals(NLE_VECTOR n1, NLE_VECTOR n2)
{
	return XMVector4AngleBetweenNormals(n1, n2);
}

inline NLE_VECTOR	NLEVector4AngleBetweenNormalsEst(NLE_VECTOR n1, NLE_VECTOR n2)
{
	return XMVector4AngleBetweenNormalsEst(n1, n2);
}

inline NLE_VECTOR	NLEVector4AngleBetweenVectors(NLE_VECTOR n1, NLE_VECTOR n2)
{
	return XMVector4AngleBetweenVectors(n1, n2);
}

inline NLE_VECTOR	NLEVector4ClampLength(NLE_VECTOR v, float lengthMin, float lengthMax)
{
	return XMVector4ClampLength(v, lengthMin, lengthMax);
}

inline NLE_VECTOR	NLEVector4ClampLengthV(NLE_VECTOR v, NLE_VECTOR lengthMin, NLE_VECTOR lengthMax)
{
	return XMVector4ClampLengthV(v, lengthMin, lengthMax);
}

inline NLE_VECTOR	NLEVector4Cross(NLE_VECTOR v1, NLE_VECTOR v2, NLE_VECTOR v3)
{
	return XMVector4Cross(v1, v2, v3);
}

inline NLE_VECTOR	NLEVector4Dot(NLE_VECTOR v1, NLE_VECTOR v2)
{
	return XMVector4Dot(v1, v2);
}

inline bool			NLEVector4InBounds(NLE_VECTOR v, NLE_VECTOR bounds)
{
	return XMVector4InBounds(v, bounds);
}

inline NLE_VECTOR	NLEVector4Length(NLE_VECTOR v)
{
	return XMVector4Length(v);
}

inline NLE_VECTOR	NLEVector4LengthEst(NLE_VECTOR v)
{
	return XMVector4LengthEst(v);
}

inline NLE_VECTOR	NLEVector4LengthSq(NLE_VECTOR v)
{
	return XMVector4LengthSq(v);
}

inline NLE_VECTOR	NLEVector4Normalize(NLE_VECTOR v)
{
	return XMVector4Normalize(v);
}

inline NLE_VECTOR	NLEVector4Orthogonal(NLE_VECTOR v)
{
	return XMVector4Orthogonal(v);
}

inline NLE_VECTOR	NLEVector4ReciprocalLength(NLE_VECTOR v)
{
	return XMVector4ReciprocalLength(v);
}

inline NLE_VECTOR	NLEVector4ReciprocalLengthEst(NLE_VECTOR v)
{
	return XMVector4ReciprocalLengthEst(v);
}

inline NLE_VECTOR	NLEVector4Reflect(NLE_VECTOR incident, NLE_VECTOR normal)
{
	return XMVector4Reflect(incident, normal);
}

inline NLE_VECTOR	NLEVector4Refract(NLE_VECTOR incident, NLE_VECTOR normal, float refractionIndex)
{
	return XMVector4Refract(incident, normal, refractionIndex);
}

inline NLE_VECTOR	NLEVector4RefractV(NLE_VECTOR incident, NLE_VECTOR normal, NLE_VECTOR refractionIndex)
{
	return XMVector4RefractV(incident, normal, refractionIndex);
}





inline NLE_VECTOR	NLEVector4Transform(NLE_VECTOR v, NLE_MATRIX m)
{
	return XMVector4Transform(v, m);
}

inline NLE_FLOAT4*	NLEVector4TransformStream(NLE_FLOAT4* outputStream, size_t outputStride,
	const NLE_FLOAT4* inputStream, size_t inputStride,
	size_t vectorCount, NLE_MATRIX m)
{
	return XMVector4TransformStream(outputStream, outputStride, inputStream, inputStride, vectorCount, m);
}