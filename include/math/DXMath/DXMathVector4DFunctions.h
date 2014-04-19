#ifndef DX_MATH_VECTOR_4D_
#define DX_MATH_VECTOR_4D_

static NLE_VECTOR	NLEVector4AngleBetweenNormals		(NLE_VECTOR n1, NLE_VECTOR n2);
static NLE_VECTOR	NLEVector4AngleBetweenNormalsEst	(NLE_VECTOR n1, NLE_VECTOR n2);
static NLE_VECTOR	NLEVector4AngleBetweenVectors		(NLE_VECTOR n1, NLE_VECTOR n2);
static NLE_VECTOR	NLEVector4ClampLength				(NLE_VECTOR v, float lengthMin, float lengthMax);
static NLE_VECTOR	NLEVector4ClampLengthV				(NLE_VECTOR v, NLE_VECTOR lengthMin, NLE_VECTOR lengthMax);
static NLE_VECTOR	NLEVector4Cross						(NLE_VECTOR v1, NLE_VECTOR v2, NLE_VECTOR v3);
static NLE_VECTOR	NLEVector4Dot						(NLE_VECTOR v1, NLE_VECTOR v2);
static bool			NLEVector4InBounds					(NLE_VECTOR v, NLE_VECTOR bounds);
static NLE_VECTOR	NLEVector4Length					(NLE_VECTOR v);
static NLE_VECTOR	NLEVector4LengthEst					(NLE_VECTOR v);
static NLE_VECTOR	NLEVector4LengthSq					(NLE_VECTOR v);
static NLE_VECTOR	NLEVector4Normalize					(NLE_VECTOR v);
static NLE_VECTOR	NLEVector4Orthogonal				(NLE_VECTOR v);
static NLE_VECTOR	NLEVector4ReciprocalLength			(NLE_VECTOR v);
static NLE_VECTOR	NLEVector4ReciprocalLengthEst		(NLE_VECTOR v);
static NLE_VECTOR	NLEVector4Reflect					(NLE_VECTOR incident, NLE_VECTOR normal);
static NLE_VECTOR	NLEVector4Refract					(NLE_VECTOR incident, NLE_VECTOR normal, float refractionIndex);
static NLE_VECTOR	NLEVector4RefractV					(NLE_VECTOR incident, NLE_VECTOR normal, NLE_VECTOR refractionIndex);

static NLE_VECTOR	NLEVector4Transform					(NLE_VECTOR v, NLE_MATRIX m);
static NLE_FLOAT4*	NLEVector4TransformStream			(NLE_FLOAT4* outputStream, size_t outputStride, 
															const NLE_FLOAT4* inputStream, size_t inputStride, 
															size_t vectorCount, NLE_MATRIX m);

#endif