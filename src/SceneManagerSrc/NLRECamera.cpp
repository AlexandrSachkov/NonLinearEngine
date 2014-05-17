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

	_position = NLREAA::alloc<NLE_VECTOR>(16);
	*_position = NLEMath::NLEVectorSet(x, y, z, 0.0f);

	_target = NLREAA::alloc<NLE_VECTOR>(16);
	*_target = NLEMath::NLEVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	_up = NLREAA::alloc<NLE_VECTOR>(16);
	*_up = NLEMath::NLEVectorSet(0.0f, 1.0f, 0.0f, 0.0f);;

	_defaultForward = NLREAA::alloc<NLE_VECTOR>(16);
	*_defaultForward = NLEMath::NLEVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	_defaultRight = NLREAA::alloc<NLE_VECTOR>(16);
	*_defaultRight = NLEMath::NLEVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	_forward = NLREAA::alloc<NLE_VECTOR>(16);
	*_forward = NLEMath::NLEVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	_right = NLREAA::alloc<NLE_VECTOR>(16);
	*_right = NLEMath::NLEVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	_view = NLREAA::alloc<NLE_MATRIX>(16);
	_projection = NLREAA::alloc<NLE_MATRIX>(16);
	*_projection = NLEMath::NLEMatrixPerspectiveFovLH(1.571f, (float)width / height, 1.0f, 1000.0f);
	//=========================
	NLE_MATRIX _rotation = NLEMath::NLEMatrixRotationRollPitchYaw(_pitch, _yaw, 0);
	*_target = NLEMath::NLEVector3TransformCoord(*_defaultForward, _rotation);
	*_target = NLEMath::NLEVector3Normalize(*_target);

	*_right = NLEMath::NLEVector3TransformCoord(*_defaultRight, _rotation);
	*_forward = NLEMath::NLEVector3TransformCoord(*_defaultForward, _rotation);
	*_up = NLEMath::NLEVector3Cross(*_forward, *_right);
	
	
	NLE_VECTOR temp = NLEMath::NLEVectorSet(
		_distanceRight * NLEMath::NLEVectorGetX(*_right), 
		_distanceRight * NLEMath::NLEVectorGetY(*_right), 
		_distanceRight * NLEMath::NLEVectorGetZ(*_right), 
		0.0f);

	*_position = NLEMath::NLEVectorAdd(*_position, temp);
	temp = NLEMath::NLEVectorSet(
		_distanceForward * NLEMath::NLEVectorGetX(*_forward),
		_distanceForward * NLEMath::NLEVectorGetY(*_forward),
		_distanceForward * NLEMath::NLEVectorGetZ(*_forward),
		0.0f);

	*_position = NLEMath::NLEVectorAdd(*_position, temp);
	temp = NLEMath::NLEVectorSet(
		_distanceUp * NLEMath::NLEVectorGetX(*_up),
		_distanceUp * NLEMath::NLEVectorGetY(*_up),
		_distanceUp * NLEMath::NLEVectorGetZ(*_up), 
		0.0f);
	*_position = NLEMath::NLEVectorAdd(*_position, temp);

	_distanceRight = 0.0f;
	_distanceForward = 0.0f;
	_distanceUp = 0.0f;

	*_target = NLEMath::NLEVectorAdd(*_position, *_target);
	*_view = NLEMath::NLEMatrixLookAtLH(*_position, *_target, *_up);
}

NLRECamera::NLRECamera(const NLRECamera& other)
{
}

NLRECamera::~NLRECamera()
{
	NLREAA::free(_viewProjection);
	NLREAA::free(_view);
	NLREAA::free(_projection);

	NLREAA::free(_defaultForward);
	NLREAA::free(_defaultRight);

	NLREAA::free(_position);
	NLREAA::free(_target);
	NLREAA::free(_up);

	NLREAA::free(_forward);
	NLREAA::free(_right);
}
