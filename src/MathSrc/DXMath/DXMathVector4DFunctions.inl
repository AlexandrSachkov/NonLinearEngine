#ifdef DX_MATH_VECTOR_4D_

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4AngleBetweenNormals(NLE_FVECTOR n1, NLE_FVECTOR n2)
{
	return DirectX::XMVector4AngleBetweenNormals(n1, n2);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4AngleBetweenNormalsEst(NLE_FVECTOR n1, NLE_FVECTOR n2)
{
	return DirectX::XMVector4AngleBetweenNormalsEst(n1, n2);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4AngleBetweenVectors(NLE_FVECTOR n1, NLE_FVECTOR n2)
{
	return DirectX::XMVector4AngleBetweenVectors(n1, n2);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4ClampLength(NLE_FVECTOR v, float lengthMin, float lengthMax)
{
	return DirectX::XMVector4ClampLength(v, lengthMin, lengthMax);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4ClampLengthV(NLE_FVECTOR v, NLE_FVECTOR lengthMin, NLE_FVECTOR lengthMax)
{
	return DirectX::XMVector4ClampLengthV(v, lengthMin, lengthMax);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Cross(NLE_FVECTOR v1, NLE_FVECTOR v2, NLE_FVECTOR v3)
{
	return DirectX::XMVector4Cross(v1, v2, v3);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Dot(NLE_FVECTOR v1, NLE_FVECTOR v2)
{
	return DirectX::XMVector4Dot(v1, v2);
}

inline bool			_NLE_CALLCONV_	NLEMath::NLEVector4InBounds(NLE_FVECTOR v, NLE_FVECTOR bounds)
{
	return DirectX::XMVector4InBounds(v, bounds);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Length(NLE_FVECTOR v)
{
	return DirectX::XMVector4Length(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4LengthEst(NLE_FVECTOR v)
{
	return DirectX::XMVector4LengthEst(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4LengthSq(NLE_FVECTOR v)
{
	return DirectX::XMVector4LengthSq(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Normalize(NLE_FVECTOR v)
{
	return DirectX::XMVector4Normalize(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Orthogonal(NLE_FVECTOR v)
{
	return DirectX::XMVector4Orthogonal(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4ReciprocalLength(NLE_FVECTOR v)
{
	return DirectX::XMVector4ReciprocalLength(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4ReciprocalLengthEst(NLE_FVECTOR v)
{
	return DirectX::XMVector4ReciprocalLengthEst(v);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Reflect(NLE_FVECTOR incident, NLE_FVECTOR normal)
{
	return DirectX::XMVector4Reflect(incident, normal);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Refract(NLE_FVECTOR incident, NLE_FVECTOR normal, float refractionIndex)
{
	return DirectX::XMVector4Refract(incident, normal, refractionIndex);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4RefractV(NLE_FVECTOR incident, NLE_FVECTOR normal, NLE_FVECTOR refractionIndex)
{
	return DirectX::XMVector4RefractV(incident, normal, refractionIndex);
}




inline NLE_VECTOR	_NLE_CALLCONV_ NLEMath::NLEVectorSet(float x, float y, float z, float w)
{
	return NLEVectorSet(x, y, z, w);
}

inline NLE_VECTOR	_NLE_CALLCONV_	NLEMath::NLEVector4Transform(NLE_FVECTOR v, NLE_FMATRIX m)
{
	return DirectX::XMVector4Transform(v, m);
}

inline NLE_FLOAT4*	_NLE_CALLCONV_	NLEMath::NLEVector4TransformStream(NLE_FLOAT4* outputStream, size_t outputStride,
	const NLE_FLOAT4* inputStream, size_t inputStride,
	size_t vectorCount,  NLE_FMATRIX m)
{
	return DirectX::XMVector4TransformStream(outputStream, outputStride, inputStream, inputStride, vectorCount, m);
}

inline NLE_VECTOR	NLEMath::NLEVectorZero()
{
	return DirectX::XMVectorZero();
}

#endif