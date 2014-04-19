#ifndef DX_MATRIX_FUNCTIONS_
#define DX_MATRIX_FUNCTIONS_

static NLE_MATRIX&	NLEMatrixAffineTransformation(const NLE_VECTOR& scaling, const NLE_VECTOR& rotationOrigin,
	const NLE_VECTOR& rotationQuaternion, const NLE_VECTOR& translation);
static NLE_MATRIX&	NLEMatrixAffineTransformation2D(const NLE_VECTOR& scaling, const NLE_VECTOR& rotationOrigin,
	float rotation, const NLE_VECTOR& translation);
static bool			NLEMatrixDecompose(const NLE_VECTOR* outScale, NLE_VECTOR* outRotQuat, NLE_VECTOR* outTrans, const  NLE_MATRIX& m);
static NLE_VECTOR&	NLEMatrixDeterminant(const NLE_MATRIX& m);
static NLE_MATRIX&	NLEMatrixIdentity				();
static NLE_MATRIX&	NLEMatrixInverse(NLE_VECTOR* pDeterminant, const NLE_MATRIX& m);
static bool			NLEMatrixIsIdentity(const NLE_MATRIX& m);
static bool			NLEMatrixIsInfinite(const NLE_MATRIX& m);
static bool			NLEMatrixIsNaN(const NLE_MATRIX& m);
static NLE_MATRIX&	NLEMatrixLookAtLH(const NLE_VECTOR& eyePosition, const NLE_VECTOR& focusPosition, const NLE_VECTOR& upDirection);
static NLE_MATRIX&	NLEMatrixLookAtRH(const NLE_VECTOR& eyePosition, const NLE_VECTOR& focusPosition, const NLE_VECTOR& upDirection);
static NLE_MATRIX&	NLEMatrixMultiply(const NLE_MATRIX& m1, const NLE_MATRIX& m2);
static NLE_MATRIX&	NLEMatrixMultiplyTranspose(const NLE_MATRIX& m1, const NLE_MATRIX& m2);
static NLE_MATRIX&	NLEMatrixOrthographicLH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixOrthographicOffCenterLH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixOrthographicOffCenterRH(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixOrthographicRH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixPerspectiveFovLH		(float fovAngleY, float aspectRatio, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixPerspectiveFovRH		(float fovAngleY, float aspectRatio, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixPerspectiveLH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixPerspectiveOffCenterLH	(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixPerspectiveOffCenterRH	(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixPerspectiveRH			(float viewWidth, float viewHeight, float nearZ, float farZ);
static NLE_MATRIX&	NLEMatrixReflect(const NLE_VECTOR& reflectionPlane);
static NLE_MATRIX&	NLEMatrixRotationAxis(const NLE_VECTOR& axis, float angle);
static NLE_MATRIX&	NLEMatrixRotationNormal(const NLE_VECTOR& normalAxis, float angle);
static NLE_MATRIX&	NLEMatrixRotationQuaternion(const NLE_VECTOR& quaternion);
static NLE_MATRIX&	NLEMatrixRotationRollPitchYaw	(float pitch, float yaw, float roll);
static NLE_MATRIX&	NLEMatrixRotationRollPitchYawFromVector(const NLE_VECTOR& angles);
static NLE_MATRIX&	NLEMatrixRotationX				(float angle);
static NLE_MATRIX&	NLEMatrixRotationY				(float angle);
static NLE_MATRIX&	NLEMatrixRotationZ				(float angle);
static NLE_MATRIX&	NLEMatrixScaling				(float scaleX, float scaleY, float scaleZ);
static NLE_MATRIX&	NLEMatrixScalingFromVector(const NLE_VECTOR& scale);
static NLE_MATRIX&	NLEMatrixSet					(float m00, float m01, float m02, float m03,
														float m10, float m11, float m12, float m13,
														float m20, float m21, float m22, float m23,
														float m30, float m31, float m32, float m33);
static NLE_MATRIX&	NLEMatrixShadow(const NLE_VECTOR& shadowPlane, const NLE_VECTOR& lightPosition);
static NLE_MATRIX&	NLEMatrixTransformation(const NLE_VECTOR& scalingOrigin, const NLE_VECTOR& scalingOrientationQuaternion,
	const NLE_VECTOR& scaling, const NLE_VECTOR& rotaionOrigin,
	const NLE_VECTOR& rotationQuaternion, const NLE_VECTOR& translation);
static NLE_MATRIX&	NLEMatrixTransformation2D(const NLE_VECTOR& scalingOrigin, float scalingOrientation,
	const NLE_VECTOR& scaling, const NLE_VECTOR& rotaionOrigin,
	float rotation, const NLE_VECTOR& translation);
static NLE_MATRIX&	NLEMatrixTranslation			(float offsetX, float offsetY, float offsetZ);
static NLE_MATRIX&	NLEMatrixTranslationFromVector(const NLE_VECTOR& offset);
static NLE_MATRIX&	NLEMatrixTranspose(const NLE_MATRIX& m);

#endif