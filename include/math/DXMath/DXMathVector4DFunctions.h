#ifndef DX_MATH_VECTOR_4D_
#define DX_MATH_VECTOR_4D_

namespace NLEMath
{
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4AngleBetweenNormals(NLE_FVECTOR n1, NLE_FVECTOR n2);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4AngleBetweenNormalsEst(NLE_FVECTOR n1, NLE_FVECTOR n2);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4AngleBetweenVectors(NLE_FVECTOR n1, NLE_FVECTOR n2);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ClampLength(NLE_FVECTOR v, float lengthMin, float lengthMax);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ClampLengthV(NLE_FVECTOR v, NLE_FVECTOR lengthMin, NLE_FVECTOR lengthMax);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Cross(NLE_FVECTOR v1, NLE_FVECTOR v2, NLE_FVECTOR v3);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Dot(NLE_FVECTOR v1, NLE_FVECTOR v2);
	bool			_NLE_CALLCONV_ NLEVector4InBounds(NLE_FVECTOR v, NLE_FVECTOR bounds);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Length(NLE_FVECTOR v);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4LengthEst(NLE_FVECTOR v);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4LengthSq(NLE_FVECTOR v);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Normalize(NLE_FVECTOR v);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Orthogonal(NLE_FVECTOR v);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ReciprocalLength(NLE_FVECTOR v);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ReciprocalLengthEst(NLE_FVECTOR v);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Reflect(NLE_FVECTOR incident, NLE_FVECTOR normal);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Refract(NLE_FVECTOR incident, NLE_FVECTOR normal, float refractionIndex);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4RefractV(NLE_FVECTOR incident, NLE_FVECTOR normal, NLE_FVECTOR refractionIndex);

	NLE_VECTOR	_NLE_CALLCONV_ NLEVectorSet(float x, float y, float z, float w);
	NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Transform(NLE_FVECTOR v, NLE_FMATRIX m);
	NLE_FLOAT4*	_NLE_CALLCONV_ NLEVector4TransformStream(NLE_FLOAT4* outputStream, size_t outputStride,
		const NLE_FLOAT4* inputStream, size_t inputStride,
		size_t vectorCount, NLE_FMATRIX m);
	NLE_VECTOR					NLEVectorZero();
}

#include "MathSrc\DXMath\DXMathVector4DFunctions.inl"
#endif