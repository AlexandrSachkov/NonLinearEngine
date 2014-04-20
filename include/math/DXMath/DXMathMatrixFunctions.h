#ifndef DX_MATRIX_FUNCTIONS_
#define DX_MATRIX_FUNCTIONS_

static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixAffineTransformation(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
	NLE_FVECTOR rotationQuaternion, NLE_GVECTOR translation);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixAffineTransformation2D(NLE_FVECTOR scaling, NLE_FVECTOR rotationOrigin,
	float rotation, NLE_FVECTOR translation);
static bool			_NLE_CALLCONV_ NLEMatrixDecompose(NLE_VECTOR* outScale, NLE_VECTOR* outRotQuat, NLE_VECTOR* outTrans, NLE_FMATRIX m);
static NLE_VECTOR	_NLE_CALLCONV_ NLEMatrixDeterminant(NLE_FMATRIX m);
static NLE_MATRIX					NLEMatrixIdentity();
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixInverse(NLE_VECTOR* pDeterminant, NLE_FMATRIX m);
static bool			_NLE_CALLCONV_ NLEMatrixIsIdentity(NLE_FMATRIX m);
static bool			_NLE_CALLCONV_ NLEMatrixIsInfinite(NLE_FMATRIX m);
static bool			_NLE_CALLCONV_ NLEMatrixIsNaN(NLE_FMATRIX m);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixLookAtLH(NLE_FVECTOR eyePosition, NLE_FVECTOR focusPosition, NLE_FVECTOR upDirection);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixLookAtRH(NLE_FVECTOR eyePosition, NLE_FVECTOR focusPosition, NLE_FVECTOR upDirection);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixMultiply(NLE_FMATRIX m1, NLE_CMATRIX m2);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixMultiplyTranspose(NLE_FMATRIX m1, NLE_CMATRIX m2);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicLH(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixOrthographicRH(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveFovLH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveFovRH(float fovAngleY, float aspectRatio, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveLH(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixPerspectiveRH(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixReflect(NLE_FVECTOR reflectionPlane);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationAxis(NLE_FVECTOR axis, float angle);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationNormal(NLE_FVECTOR normalAxis, float angle);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationQuaternion(NLE_FVECTOR quaternion);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationRollPitchYaw(float pitch, float yaw, float roll);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationRollPitchYawFromVector(NLE_FVECTOR angles);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationX(float angle);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationY(float angle);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixRotationZ(float angle);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixScaling(float scaleX, float scaleY, float scaleZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixScalingFromVector(NLE_FVECTOR scale);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixSet(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixShadow(NLE_FVECTOR shadowPlane, NLE_FVECTOR lightPosition);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTransformation(NLE_FVECTOR scalingOrigin, NLE_FVECTOR scalingOrientationQuaternion,
	NLE_FVECTOR scaling, NLE_GVECTOR rotaionOrigin,
	NLE_HVECTOR rotationQuaternion, NLE_HVECTOR translation);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTransformation2D(NLE_FVECTOR scalingOrigin, float scalingOrientation,
	NLE_FVECTOR scaling, NLE_FVECTOR rotaionOrigin,
	float rotation, NLE_GVECTOR translation);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranslation(float offsetX, float offsetY, float offsetZ);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranslationFromVector(NLE_FVECTOR offset);
static NLE_MATRIX	_NLE_CALLCONV_ NLEMatrixTranspose(NLE_FMATRIX m);

#endif