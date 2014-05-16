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

#ifdef DX_MATRIX_FUNCTIONS_

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixAffineTransformation(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
	NLE_FVECTOR rotationQuaternion, NLE_GVECTOR translation)
{
	return DirectX::XMMatrixAffineTransformation(scaling, rotationOrigin, rotationQuaternion, translation);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixAffineTransformation2D(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
	float rotation, NLE_FVECTOR translation)
{
	return DirectX::XMMatrixAffineTransformation2D(scaling, rotationOrigin, rotation, translation);
}

inline bool _NLE_CALLCONV_ NLEMath::NLEMatrixDecompose(NLE_VECTOR* outScale, NLE_VECTOR* outRotQuat, NLE_VECTOR* outTrans, NLE_FMATRIX m)
{
	return DirectX::XMMatrixDecompose(outScale, outRotQuat, outTrans, m);
}

inline NLE_VECTOR	_NLE_CALLCONV_ NLEMath::NLEMatrixDeterminant(NLE_FMATRIX m)
{
	return DirectX::XMMatrixDeterminant(m);
}

inline NLE_MATRIX	NLEMath::NLEMatrixIdentity()
{
	return DirectX::XMMatrixIdentity();
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixInverse(NLE_VECTOR* pDeterminant, NLE_FMATRIX m)
{
	return DirectX::XMMatrixInverse(pDeterminant, m);
}

inline bool			_NLE_CALLCONV_ NLEMath::NLEMatrixIsIdentity(NLE_FMATRIX m)
{
	return DirectX::XMMatrixIsIdentity(m);
}

inline bool			_NLE_CALLCONV_ NLEMath::NLEMatrixIsInfinite(NLE_FMATRIX m)
{
	return DirectX::XMMatrixIsInfinite(m);
}

inline bool			_NLE_CALLCONV_ NLEMath::NLEMatrixIsNaN(NLE_FMATRIX m)
{
	return DirectX::XMMatrixIsNaN(m);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixLookAtLH(NLE_FVECTOR eyePosition, NLE_FVECTOR focusPosition, NLE_FVECTOR upDirection)
{
	return DirectX::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixLookAtRH(NLE_FVECTOR eyePosition, NLE_FVECTOR focusPosition, NLE_FVECTOR upDirection)
{
	return DirectX::XMMatrixLookAtRH(eyePosition, focusPosition, upDirection);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixMultiply(NLE_FMATRIX m1, NLE_CMATRIX m2)
{
	return DirectX::XMMatrixMultiply(m1, m2);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixMultiplyTranspose(NLE_FMATRIX m1, NLE_CMATRIX m2)
{
	return DirectX::XMMatrixMultiplyTranspose(m1, m2);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixOrthographicLH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixOrthographicRH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicRH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixPerspectiveFovRH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovRH(fovAngleY, aspectRatio, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixPerspectiveLH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveLH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixPerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixPerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixPerspectiveRH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveRH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixReflect(NLE_FVECTOR reflectionPlane)
{
	return DirectX::XMMatrixReflect(reflectionPlane);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationAxis(NLE_FVECTOR axis, float angle)
{
	return DirectX::XMMatrixRotationAxis(axis, angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationNormal(NLE_FVECTOR normalAxis, float angle)
{
	return DirectX::XMMatrixRotationNormal(normalAxis, angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationQuaternion(NLE_FVECTOR quaternion)
{
	return DirectX::XMMatrixRotationQuaternion(quaternion);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationRollPitchYaw(float pitch, float yaw, float roll)
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationRollPitchYawFromVector(NLE_FVECTOR angles)
{
	return DirectX::XMMatrixRotationRollPitchYawFromVector(angles);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationX(float angle)
{
	return DirectX::XMMatrixRotationX(angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationY(float angle)
{
	return DirectX::XMMatrixRotationY(angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixRotationZ(float angle)
{
	return DirectX::XMMatrixRotationZ(angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixScaling(float scaleX, float scaleY, float scaleZ)
{
	return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixScalingFromVector(NLE_FVECTOR scale)
{
	return DirectX::XMMatrixScalingFromVector(scale);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixSet(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	return DirectX::XMMatrixSet(m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixShadow(NLE_FVECTOR shadowPlane, NLE_FVECTOR lightPosition)
{
	return DirectX::XMMatrixShadow(shadowPlane, lightPosition);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixTransformation(NLE_FVECTOR scalingOrigin, NLE_FVECTOR scalingOrientationQuaternion,
	NLE_FVECTOR scaling, NLE_GVECTOR rotaionOrigin,
	NLE_HVECTOR rotationQuaternion, NLE_HVECTOR translation)
{
	return DirectX::XMMatrixTransformation(scalingOrigin, scalingOrientationQuaternion,
		scaling, rotaionOrigin,
		rotationQuaternion, translation);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixTransformation2D(NLE_FVECTOR scalingOrigin, float scalingOrientation,
	NLE_FVECTOR scaling, NLE_FVECTOR rotaionOrigin,
	float rotation, NLE_GVECTOR translation)
{
	return DirectX::XMMatrixTransformation2D(scalingOrigin, scalingOrientation,
		scaling, rotaionOrigin,
		rotation, translation);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixTranslation(float offsetX, float offsetY, float offsetZ)
{
	return DirectX::XMMatrixTranslation(offsetX, offsetY, offsetZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixTranslationFromVector(NLE_FVECTOR offset)
{
	return DirectX::XMMatrixTranslationFromVector(offset);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMath::NLEMatrixTranspose(NLE_FMATRIX m)
{
	return DirectX::XMMatrixTranspose(m);
}


#endif