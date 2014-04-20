#include "stdafx.h"
#include "math\DXMath\DXMathMatrixFunctions.h"

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixAffineTransformation(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
	NLE_FVECTOR rotationQuaternion, NLE_GVECTOR translation)
{
	return DirectX::XMMatrixAffineTransformation(scaling, rotationOrigin, rotationQuaternion, translation);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixAffineTransformation2D(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
	float rotation, NLE_FVECTOR translation)
{
	return DirectX::XMMatrixAffineTransformation2D(scaling, rotationOrigin, rotation, translation);
}

inline bool _NLE_CALLCONV_ NLEMatrixDecompose(NLE_VECTOR* outScale, NLE_VECTOR* outRotQuat, NLE_VECTOR* outTrans, NLE_FMATRIX m)
{
	return DirectX::XMMatrixDecompose(outScale, outRotQuat, outTrans, m);
}

inline NLE_VECTOR	_NLE_CALLCONV_ NLEMatrixDeterminant( NLE_FMATRIX m)
{
	return DirectX::XMMatrixDeterminant(m);
}

inline NLE_MATRIX	NLEMatrixIdentity			()
{
	return DirectX::XMMatrixIdentity();
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixInverse(NLE_VECTOR* pDeterminant,  NLE_FMATRIX m)
{
	return DirectX::XMMatrixInverse(pDeterminant, m);
}

inline bool			_NLE_CALLCONV_ NLEMatrixIsIdentity( NLE_FMATRIX m)
{
	return DirectX::XMMatrixIsIdentity(m);
}

inline bool			_NLE_CALLCONV_ NLEMatrixIsInfinite( NLE_FMATRIX m)
{
	return DirectX::XMMatrixIsInfinite(m);
}

inline bool			_NLE_CALLCONV_ NLEMatrixIsNaN( NLE_FMATRIX m)
{
	return DirectX::XMMatrixIsNaN(m);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixLookAtLH( NLE_FVECTOR eyePosition,  NLE_FVECTOR focusPosition,  NLE_FVECTOR upDirection)
{
	return DirectX::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixLookAtRH( NLE_FVECTOR eyePosition,  NLE_FVECTOR focusPosition,  NLE_FVECTOR upDirection)
{
	return DirectX::XMMatrixLookAtRH(eyePosition, focusPosition, upDirection);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixMultiply( NLE_FMATRIX m1,  NLE_CMATRIX m2)
{
	return DirectX::XMMatrixMultiply(m1, m2);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixMultiplyTranspose( NLE_FMATRIX m1,  NLE_CMATRIX m2)
{
	return DirectX::XMMatrixMultiplyTranspose(m1, m2);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicLH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicRH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixOrthographicRH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveFovRH(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveFovRH(fovAngleY, aspectRatio, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveLH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveLH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveRH(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return DirectX::XMMatrixPerspectiveRH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixReflect( NLE_FVECTOR reflectionPlane)
{
	return DirectX::XMMatrixReflect(reflectionPlane);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationAxis( NLE_FVECTOR axis, float angle)
{
	return DirectX::XMMatrixRotationAxis(axis, angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationNormal( NLE_FVECTOR normalAxis, float angle)
{
	return DirectX::XMMatrixRotationNormal(normalAxis, angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationQuaternion( NLE_FVECTOR quaternion)
{
	return DirectX::XMMatrixRotationQuaternion(quaternion);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationRollPitchYaw(float pitch, float yaw, float roll)
{
	return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationRollPitchYawFromVector( NLE_FVECTOR angles)
{
	return DirectX::XMMatrixRotationRollPitchYawFromVector(angles);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationX(float angle)
{
	return NLEMatrixRotationX(angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationY(float angle)
{
	return NLEMatrixRotationY(angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationZ(float angle)
{
	return NLEMatrixRotationZ(angle);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixScaling(float scaleX, float scaleY, float scaleZ)
{
	return DirectX::XMMatrixScaling(scaleX, scaleY, scaleZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixScalingFromVector( NLE_FVECTOR scale)
{
	return DirectX::XMMatrixScalingFromVector(scale);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixSet(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	return DirectX::XMMatrixSet(m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixShadow( NLE_FVECTOR shadowPlane,  NLE_FVECTOR lightPosition)
{
	return DirectX::XMMatrixShadow(shadowPlane, lightPosition);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTransformation(NLE_FVECTOR scalingOrigin, NLE_FVECTOR scalingOrientationQuaternion,
	NLE_FVECTOR scaling, NLE_GVECTOR rotaionOrigin,
	NLE_HVECTOR rotationQuaternion, NLE_HVECTOR translation)
{
	return DirectX::XMMatrixTransformation(scalingOrigin, scalingOrientationQuaternion,
		scaling, rotaionOrigin,
		rotationQuaternion, translation);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTransformation2D(NLE_FVECTOR scalingOrigin, float scalingOrientation,
	NLE_FVECTOR scaling, NLE_FVECTOR rotaionOrigin,
	float rotation, NLE_GVECTOR translation)
{
	return DirectX::XMMatrixTransformation2D(scalingOrigin, scalingOrientation,
		scaling, rotaionOrigin,
		rotation, translation);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranslation(float offsetX, float offsetY, float offsetZ)
{
	return DirectX::XMMatrixTranslation(offsetX, offsetY, offsetZ);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranslationFromVector( NLE_FVECTOR offset)
{
	return DirectX::XMMatrixTranslationFromVector(offset);
}

inline NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranspose( NLE_FMATRIX m)
{
	return DirectX::XMMatrixTranspose(m);
}