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

#include "NLREMain\stdafx.h"
#include "SceneManager\NLRECamera.h"


NLRECamera::NLRECamera(float x, float y, float z, int width, int height)
{
	_fullRotation = 6.283f;

	_initXPos = x;
	_initYPos = y;
	_initZPos = z;

	_fov = _fullRotation / 4;
	_nearZ = 1.0f;
	_farZ = 1000.0f;
	_width = width;
	_height = height;

	_hasMoved = true;

	_position = NLREAA::alloc<NLE_VECTOR>(16);
	_target = NLREAA::alloc<NLE_VECTOR>(16);
	_up = NLREAA::alloc<NLE_VECTOR>(16);

	_defaultForward = NLREAA::alloc<NLE_VECTOR>(16);
	*_defaultForward = NLEMath::NLEVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	_defaultRight = NLREAA::alloc<NLE_VECTOR>(16);
	*_defaultRight = NLEMath::NLEVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	_forward = NLREAA::alloc<NLE_VECTOR>(16);
	_right = NLREAA::alloc<NLE_VECTOR>(16);

	_view = NLREAA::alloc<NLE_MATRIX>(16);
	_projection = NLREAA::alloc<NLE_MATRIX>(16);
	_viewProjection = NLREAA::alloc<NLE_MATRIX>(16);

	*_projection = NLEMath::NLEMatrixPerspectiveFovLH(_fov, (float)_width / _height, _nearZ, _farZ);
	
	reset();
	update();
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

void NLRECamera::reset()
{
	_movementSensitivity = 0.2f;
	_rotationSensitivity = 0.01f;

	_distanceForward = 0.0f;
	_distanceRight = 0.0f;
	_distanceUp = 0.0f;

	_pitch = 0.0f;
	_yaw = 0.0f;

	*_position = NLEMath::NLEVectorSet(_initXPos, _initYPos, _initZPos, 0.0f);

	_hasMoved = true;
}

void NLRECamera::update()
{
	if (!_hasMoved) return;

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
	*_viewProjection = *_view * *_projection;

	_hasMoved = false;
}

void NLRECamera::changeFoV(float fov)
{
	_fov = fov;
	*_projection = NLEMath::NLEMatrixPerspectiveFovLH(_fov, (float)_width / _height, _nearZ, _farZ);
}

void NLRECamera::changeViewport(unsigned int width, unsigned int height)
{
	_width = width;
	_height = height;
	*_projection = NLEMath::NLEMatrixPerspectiveFovLH(_fov, (float)_width / _height, _nearZ, _farZ);
}

void NLRECamera::changeViewDistance(float nearZ, float farZ)
{
	_nearZ = nearZ;
	_farZ = farZ;
	*_projection = NLEMath::NLEMatrixPerspectiveFovLH(_fov, (float)_width / _height, _nearZ, _farZ);
}

NLE_MATRIX NLRECamera::getViewProjection()
{
	return *_viewProjection;
}

void NLRECamera::setSensitivity(float movementSensitivity, float rotationSensitivity)
{
	_movementSensitivity = movementSensitivity;
	_rotationSensitivity = rotationSensitivity;
}

void NLRECamera::rotate(float yaw, float pitch)
{
	if (NLEMath::NLEVectorGetY(*_up) > 0) _yaw += yaw * _rotationSensitivity;
	else _yaw -= yaw * _rotationSensitivity;

	if (_yaw <= -_fullRotation) _yaw += _fullRotation;
	else if (_yaw >= _fullRotation) _yaw -= _fullRotation;

	_pitch += pitch * _rotationSensitivity;
	if (_pitch <= -_fullRotation) _pitch += _fullRotation;
	else if (_pitch >= _fullRotation) _pitch -= _fullRotation;

	_hasMoved = true;
}

void NLRECamera::pitchUp()
{
	_pitch += _rotationSensitivity;
	if (_pitch >= _fullRotation) _pitch -= _fullRotation;
	_hasMoved = true;
}

void NLRECamera::pitchDown()
{
	_pitch -= _rotationSensitivity;
	if (_pitch <= -_fullRotation) _pitch += _fullRotation;
	_hasMoved = true;
}

void NLRECamera::yawLeft()
{
	_yaw -= _rotationSensitivity;
	if (_yaw <= -_fullRotation) _yaw += _fullRotation;
	_hasMoved = true;
}

void NLRECamera::yawRight()
{
	_yaw += _rotationSensitivity;
	if (_yaw >= _fullRotation) _yaw -= _fullRotation;
	_hasMoved = true;
}

void NLRECamera::moveForward()
{
	_distanceForward += _movementSensitivity;
	_hasMoved = true;
}

void NLRECamera::moveBackward()
{
	_distanceForward -= _movementSensitivity;
	_hasMoved = true;
}

void NLRECamera::moveLeft()
{
	_distanceRight -= _movementSensitivity;
	_hasMoved = true;
}

void NLRECamera::moveRight()
{
	_distanceRight += _movementSensitivity;
	_hasMoved = true;
}

void NLRECamera::moveUp()
{
	_distanceUp += _movementSensitivity;
	_hasMoved = true;
}

void NLRECamera::moveDown()
{
	_distanceUp -= _movementSensitivity;
	_hasMoved = true;
}
