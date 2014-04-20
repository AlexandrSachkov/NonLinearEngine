#ifndef DX_MATH_VECTOR_4D_
#define DX_MATH_VECTOR_4D_

static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4AngleBetweenNormals(NLE_FVECTOR n1, NLE_FVECTOR n2);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4AngleBetweenNormalsEst(NLE_FVECTOR n1, NLE_FVECTOR n2);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4AngleBetweenVectors(NLE_FVECTOR n1, NLE_FVECTOR n2);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ClampLength(NLE_FVECTOR v, float lengthMin, float lengthMax);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ClampLengthV(NLE_FVECTOR v, NLE_FVECTOR lengthMin, NLE_FVECTOR lengthMax);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Cross(NLE_FVECTOR v1, NLE_FVECTOR v2, NLE_FVECTOR v3);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Dot(NLE_FVECTOR v1, NLE_FVECTOR v2);
static bool			_NLE_CALLCONV_ NLEVector4InBounds(NLE_FVECTOR v, NLE_FVECTOR bounds);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Length(NLE_FVECTOR v);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4LengthEst(NLE_FVECTOR v);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4LengthSq(NLE_FVECTOR v);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Normalize(NLE_FVECTOR v);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Orthogonal(NLE_FVECTOR v);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ReciprocalLength(NLE_FVECTOR v);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4ReciprocalLengthEst(NLE_FVECTOR v);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Reflect(NLE_FVECTOR incident, NLE_FVECTOR normal);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Refract(NLE_FVECTOR incident, NLE_FVECTOR normal, float refractionIndex);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4RefractV(NLE_FVECTOR incident, NLE_FVECTOR normal, NLE_FVECTOR refractionIndex);

static NLE_VECTOR	_NLE_CALLCONV_ NLEVectorSet(float x, float y, float z, float w);
static NLE_VECTOR	_NLE_CALLCONV_ NLEVector4Transform(NLE_FVECTOR v, NLE_FMATRIX m);
static NLE_FLOAT4*	_NLE_CALLCONV_ NLEVector4TransformStream(NLE_FLOAT4* outputStream, size_t outputStride,
	const NLE_FLOAT4* inputStream, size_t inputStride,
	size_t vectorCount, NLE_FMATRIX m);
static NLE_VECTOR					NLEVectorZero();

#endif