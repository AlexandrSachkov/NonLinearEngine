#ifndef DX_MATH_VECTOR_4D_
#define DX_MATH_VECTOR_4D_

static NLE_VECTOR&	NLEVector4AngleBetweenNormals(const NLE_VECTOR& n1, const NLE_VECTOR& n2);
static NLE_VECTOR&	NLEVector4AngleBetweenNormalsEst(const NLE_VECTOR& n1, const NLE_VECTOR& n2);
static NLE_VECTOR&	NLEVector4AngleBetweenVectors(const NLE_VECTOR& n1, const NLE_VECTOR& n2);
static NLE_VECTOR&	NLEVector4ClampLength(const NLE_VECTOR& v, float lengthMin, float lengthMax);
static NLE_VECTOR&	NLEVector4ClampLengthV(const NLE_VECTOR& v, const NLE_VECTOR& lengthMin, const NLE_VECTOR& lengthMax);
static NLE_VECTOR&	NLEVector4Cross(const NLE_VECTOR& v1, const NLE_VECTOR& v2, const NLE_VECTOR& v3);
static NLE_VECTOR&	NLEVector4Dot(const NLE_VECTOR& v1, const NLE_VECTOR& v2);
static bool			NLEVector4InBounds(const NLE_VECTOR& v, const NLE_VECTOR& bounds);
static NLE_VECTOR&	NLEVector4Length(const NLE_VECTOR& v);
static NLE_VECTOR&	NLEVector4LengthEst(const NLE_VECTOR& v);
static NLE_VECTOR&	NLEVector4LengthSq(const NLE_VECTOR& v);
static NLE_VECTOR&	NLEVector4Normalize(const NLE_VECTOR& v);
static NLE_VECTOR&	NLEVector4Orthogonal(const NLE_VECTOR& v);
static NLE_VECTOR&	NLEVector4ReciprocalLength(const NLE_VECTOR& v);
static NLE_VECTOR&	NLEVector4ReciprocalLengthEst(const NLE_VECTOR& v);
static NLE_VECTOR&	NLEVector4Reflect(const NLE_VECTOR& incident, const NLE_VECTOR& normal);
static NLE_VECTOR&	NLEVector4Refract(const NLE_VECTOR& incident, const NLE_VECTOR& normal, float refractionIndex);
static NLE_VECTOR&	NLEVector4RefractV(const NLE_VECTOR& incident, const NLE_VECTOR& normal, const NLE_VECTOR& refractionIndex);

static NLE_VECTOR&	NLEVector4Transform(const NLE_VECTOR& v, const NLE_MATRIX& m);
static NLE_FLOAT4*	NLEVector4TransformStream			(NLE_FLOAT4* outputStream, size_t outputStride, 
															const NLE_FLOAT4* inputStream, size_t inputStride, 
															size_t vectorCount, const NLE_MATRIX& m);

#endif