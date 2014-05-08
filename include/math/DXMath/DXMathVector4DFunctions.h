/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 NonLinear Rendering Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

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