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

#include "stdafx.h"
#include "SceneManager\NLRECamera.h"


NLRECamera::NLRECamera(float x, float y, float z, int width, int height)
{
	_movementSensitivity = 10.0f;
	_rotationSensitivity = 10.0f;

	_distanceForward = 0.0f;
	_distanceRight = 0.0f;
	_distanceUp = 0.0f;

	_pitch = 0.0f;
	_yaw = 0.0f;
	_roll = 0.0f;

	NLE_VECTOR defaultForward = NLEMath::NLEVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	NLE_VECTOR defaultRight = NLEMath::NLEVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	NLE_VECTOR defaultUp = NLEMath::NLEVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	NLE_VECTOR forward = NLEMath::NLEVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	NLE_VECTOR right = NLEMath::NLEVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	NLE_VECTOR up = NLEMath::NLEVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	NLE_MATRIX rotation = NLEMath::NLEMatrixRotationRollPitchYaw(_pitch, _yaw, _roll);
	NLE_VECTOR target = NLEMath::NLEVector3TransformCoord(defaultForward, rotation);
	target = NLEMath::NLEVector3Normalize(target);

	NLE_MATRIX RotateYTempMatrix;
	RotateYTempMatrix = NLEMath::NLEMatrixRotationY(_yaw);

	right = XMVector3TransformCoord(defaultRight, RotateYTempMatrix);
	up = XMVector3TransformCoord(up, RotateYTempMatrix);
	forward = XMVector3TransformCoord(defaultForward, RotateYTempMatrix);
	/*
	NLE_VECTOR camPosition;
	camPosition = (_distanceRight *right);
	camPosition += _distanceForward*forward;
	DirectX::XMVECTOR oneVect;
	DirectX::XMVECTOR otherVect;
	oneVect += (oneVect * otherVect);
	_distanceRight = 0.0f;
	_distanceForward = 0.0f;

	NLE_VECTOR camTarget = camPosition + camTarget;

	camView = XMMatrixLookAtLH(camPosition, camTarget, up);
	*/
}

NLRECamera::NLRECamera(const NLRECamera& other)
{
}

NLRECamera::~NLRECamera()
{

}
