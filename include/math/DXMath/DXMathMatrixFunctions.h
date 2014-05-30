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

#ifndef DX_MATRIX_FUNCTIONS_
#define DX_MATRIX_FUNCTIONS_

namespace NLEMath
{
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixAffineTransformation(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
		NLE_FVECTOR rotationQuaternion, NLE_GVECTOR translation);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixAffineTransformation2D(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
		float rotation, NLE_FVECTOR translation);
	bool		_NLE_CALLCONV_ NLEMatrixDecompose(NLE_VECTOR* outScale, NLE_VECTOR* outRotQuat, NLE_VECTOR* outTrans, NLE_FMATRIX m);
	NLE_VECTOR	_NLE_CALLCONV_ NLEMatrixDeterminant(NLE_FMATRIX m);
	NLE_MATRIX					NLEMatrixIdentity();
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixInverse(NLE_VECTOR* pDeterminant, NLE_FMATRIX m);
	bool		_NLE_CALLCONV_ NLEMatrixIsIdentity(NLE_FMATRIX m);
	bool		_NLE_CALLCONV_ NLEMatrixIsInfinite(NLE_FMATRIX m);
	bool		_NLE_CALLCONV_ NLEMatrixIsNaN(NLE_FMATRIX m);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixLookAtLH(NLE_FVECTOR eyePosition, NLE_FVECTOR focusPosition, NLE_FVECTOR upDirection);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixLookAtRH(NLE_FVECTOR eyePosition, NLE_FVECTOR focusPosition, NLE_FVECTOR upDirection);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixMultiply(NLE_FMATRIX m1, NLE_CMATRIX m2);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixMultiplyTranspose(NLE_FMATRIX m1, NLE_CMATRIX m2);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicLH(float viewWidth, float viewHeight, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicRH(float viewWidth, float viewHeight, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveFovRH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveLH(float viewWidth, float viewHeight, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveRH(float viewWidth, float viewHeight, float nearZ, float farZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixReflect(NLE_FVECTOR reflectionPlane);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationAxis(NLE_FVECTOR axis, float angle);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationNormal(NLE_FVECTOR normalAxis, float angle);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationQuaternion(NLE_FVECTOR quaternion);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationRollPitchYaw(float pitch, float yaw, float roll);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationRollPitchYawFromVector(NLE_FVECTOR angles);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationX(float angle);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationY(float angle);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationZ(float angle);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixScaling(float scaleX, float scaleY, float scaleZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixScalingFromVector(NLE_FVECTOR scale);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixSet(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixShadow(NLE_FVECTOR shadowPlane, NLE_FVECTOR lightPosition);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTransformation(NLE_FVECTOR scalingOrigin, NLE_FVECTOR scalingOrientationQuaternion,
		NLE_FVECTOR scaling, NLE_GVECTOR rotaionOrigin,
		NLE_HVECTOR rotationQuaternion, NLE_HVECTOR translation);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTransformation2D(NLE_FVECTOR scalingOrigin, float scalingOrientation,
		NLE_FVECTOR scaling, NLE_FVECTOR rotaionOrigin,
		float rotation, NLE_GVECTOR translation);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranslation(float offsetX, float offsetY, float offsetZ);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranslationFromVector(NLE_FVECTOR offset);
	NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranspose(NLE_FMATRIX m);
}
#include "math\DXMath\DXMathMatrixFunctions.inl"

#endif