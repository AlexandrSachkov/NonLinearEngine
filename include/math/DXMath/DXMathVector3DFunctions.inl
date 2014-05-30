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

#ifdef DX_MATH_VECTOR_3D_

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3Cross(NLE_FVECTOR v1, NLE_FVECTOR v2)
{
	return DirectX::XMVector3Cross(v1, v2);
}

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3InverseRotate(NLE_FVECTOR v, NLE_FVECTOR rotationQuaternion)
{
	return DirectX::XMVector3InverseRotate(v, rotationQuaternion);
}

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3Normalize(NLE_FVECTOR v)
{
	return DirectX::XMVector3Normalize(v);
}

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3Project(
	NLE_FVECTOR v,
	float viewportX,
	float viewportY,
	float viewportWidth,
	float viewportHeight,
	float viewportMinZ,
	float viewportMaxZ,
	NLE_FMATRIX projection,
	NLE_CMATRIX view,
	NLE_CMATRIX world)
{
	return DirectX::XMVector3Project(v, viewportX, viewportY, viewportWidth, viewportHeight, viewportMinZ, viewportMaxZ, projection, view, world);
}

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3Rotate(NLE_FVECTOR v, NLE_FVECTOR rotationQuaternion)
{
	return DirectX::XMVector3Rotate(v, rotationQuaternion);
}

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3Transform(NLE_FVECTOR v, NLE_FMATRIX m)
{
	return DirectX::XMVector3Transform(v, m);
}

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3TransformCoord(NLE_FVECTOR v, NLE_FMATRIX m)
{
	return DirectX::XMVector3TransformCoord(v, m);
}

inline 	NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3TransformNormal(NLE_FVECTOR v, NLE_FMATRIX m)
{
	return DirectX::XMVector3TransformNormal(v, m);
}

inline NLE_VECTOR _NLE_CALLCONV_ NLEMath::NLEVector3Unproject(
	NLE_FVECTOR v,
	float viewportX,
	float viewportY,
	float viewportWidth,
	float viewportHeight,
	float viewportMinZ,
	float viewportMaxZ,
	NLE_FMATRIX projection,
	NLE_CMATRIX view,
	NLE_CMATRIX world)
{
	return DirectX::XMVector3Unproject(v, viewportX, viewportY, viewportWidth, viewportHeight, viewportMinZ, viewportMaxZ, projection, view, world);
}
#endif