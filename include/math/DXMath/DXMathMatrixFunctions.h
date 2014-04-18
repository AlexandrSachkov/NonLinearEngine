#ifndef DX_MATRIX_FUNCTIONS_
#define DX_MATRIX_FUNCTIONS_

static NLE_MATRIX	NLEMatrixAffineTransformation	(NLE_VECTOR scaling, NLE_VECTOR rotationOrigin, 
														NLE_VECTOR rotationQuaternion, NLE_VECTOR translation);
static NLE_MATRIX	NLEMatrixAffineTransformation2D	(NLE_VECTOR scaling, NLE_VECTOR rotationOrigin,
														float rotation, NLE_VECTOR translation);
static bool			NLEMatrixDecompose				(NLE_VECTOR* outScale, NLE_VECTOR* outRotQuat, NLE_VECTOR* outTrans, NLE_MATRIX m);
static NLE_VECTOR	NLEMatrixDeterminant			(NLE_MATRIX m);
static NLE_MATRIX	NLEMatrixIdentity				();
static NLE_MATRIX	NLEMatrixInverse				(NLE_VECTOR* pDeterminant, NLE_MATRIX m);
static bool			NLEMatrixIsIdentity				(NLE_MATRIX m);
static bool			NLEMatrixIsInfinite				(NLE_MATRIX m);
static bool			NLEMatrixIsNaN					(NLE_MATRIX m);
static NLE_MATRIX	NLEMatrixLookAtLH				(NLE_VECTOR eyePosition, NLE_VECTOR focusPosition, NLE_VECTOR upDirection);
static NLE_MATRIX	NLEMatrixLookAtRH				(NLE_VECTOR eyePosition, NLE_VECTOR focusPosition, NLE_VECTOR upDirection);
static NLE_MATRIX	NLEMatrixMultiply				(NLE_MATRIX m1, NLE_MATRIX m2);
static NLE_MATRIX	NLEMatrixMultiplyTranspose		(NLE_MATRIX m1, NLE_MATRIX m2);
static NLE_MATRIX	NLEMatrixOrthographicLH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixOrthographicRH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixPerspectiveFovLH		(float fovAngleY, float aspectRatio, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixPerspectiveFovRH		(float fovAngleY, float aspectRatio, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixPerspectiveLH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixPerspectiveOffCenterLH	(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixPerspectiveOffCenterRH	(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixPerspectiveRH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX	NLEMatrixReflect				(NLE_VECTOR reflectionPlane);
static NLE_MATRIX	NLEMatrixRotationAxis			(NLE_VECTOR axis, float angle);
static NLE_MATRIX	NLEMatrixRotationNormal			(NLE_VECTOR normalAxis, float angle);
static NLE_MATRIX	NLEMatrixRotationQuaternion		(NLE_VECTOR quaternion);
static NLE_MATRIX	NLEMatrixRotationRollPitchYaw	(float pitch, float yaw, float roll);
static NLE_MATRIX	NLEMatrixRotationRollPitchYawFromVector	(NLE_VECTOR angles);
static NLE_MATRIX	NLEMatrixRotationX				(float angle);
static NLE_MATRIX	NLEMatrixRotationY				(float angle);
static NLE_MATRIX	NLEMatrixRotationZ				(float angle);
static NLE_MATRIX	NLEMatrixScaling				(float scaleX, float scaleY, float scaleZ);
static NLE_MATRIX	NLEMatrixScalingFromVector		(NLE_VECTOR scale);
static NLE_MATRIX	NLEMatrixSet					(float m00, float m01, float m02, float m03,
														float m10, float m11, float m12, float m13,
														float m20, float m21, float m22, float m23,
														float m30, float m31, float m32, float m33);
static NLE_MATRIX	NLEMatrixShadow					(NLE_VECTOR shadowPlane, NLE_VECTOR lightPosition);
static NLE_MATRIX	NLEMatrixTransformation			(NLE_VECTOR scalingOrigin, NLE_VECTOR scalingOrientationQuaternion,
														NLE_VECTOR scaling, NLE_VECTOR rotaionOrigin,
														NLE_VECTOR rotationQuaternion, NLE_VECTOR translation);
static NLE_MATRIX	NLEMatrixTransformation2D		(NLE_VECTOR scalingOrigin, float scalingOrientation,
														NLE_VECTOR scaling, NLE_VECTOR rotaionOrigin,
														float rotation, NLE_VECTOR translation);
static NLE_MATRIX	NLEMatrixTranslation			(float offsetX, float offsetY, float offsetZ);
static NLE_MATRIX	NLEMatrixTranslationFromVector	(NLE_VECTOR offset);
static NLE_MATRIX	NLEMatrixTranspose				(NLE_MATRIX m);

#endif