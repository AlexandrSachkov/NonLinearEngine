/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

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

#include "NL_Camera.h"
#include "NL_Allocator.h"

namespace NLE
{
	namespace GRAPHICS
	{
		Camera::Camera(float x, float y, float z, int width, int height)
		{
			_fullRotation = 6.28318531f;

			_initXPos = x;
			_initYPos = y;
			_initZPos = z;

			_fov = 1.13446401f;
			_nearZ = 1.0f;
			_farZ = 1000.0f;
			_width = width;
			_height = height;

			_hasMoved = true;

			_position = NLE::alloc<DirectX::XMVECTOR>(16);
			_target = NLE::alloc<DirectX::XMVECTOR>(16);
			_up = NLE::alloc<DirectX::XMVECTOR>(16);

			_defaultForward = NLE::alloc<DirectX::XMVECTOR>(16);
			*_defaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			_defaultRight = NLE::alloc<DirectX::XMVECTOR>(16);
			*_defaultRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

			_forward = NLE::alloc<DirectX::XMVECTOR>(16);
			_right = NLE::alloc<DirectX::XMVECTOR>(16);

			_view = NLE::alloc<DirectX::XMMATRIX>(16);
			_projection = NLE::alloc<DirectX::XMMATRIX>(16);
			_viewProjection = NLE::alloc<DirectX::XMMATRIX>(16);

			reset();
			update();
		}

		Camera::~Camera()
		{
			NLE::free(_viewProjection);
			NLE::free(_view);
			NLE::free(_projection);

			NLE::free(_defaultForward);
			NLE::free(_defaultRight);

			NLE::free(_position);
			NLE::free(_target);
			NLE::free(_up);

			NLE::free(_forward);
			NLE::free(_right);
		}

		void Camera::reset()
		{
			_movementSensitivity = 0.1f;
			_rotationSensitivity = 0.005f;

			_distanceForward = 0.0f;
			_distanceRight = 0.0f;

			_pitch = 0.0f;
			_yaw = 0.0f;

			*_forward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			*_right = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

			*_position = DirectX::XMVectorSet(_initXPos, _initYPos, _initZPos, 0.0f);
			*_target = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			*_up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

			*_view = DirectX::XMMatrixLookAtLH(*_position, *_target, *_up);
			*_projection = DirectX::XMMatrixPerspectiveFovLH(_fov, static_cast<float>(_width / _height), _nearZ, _farZ);
			*_viewProjection = (*_view) * (*_projection);

			_hasMoved = true;
		}

		void Camera::update()
		{
			if (!_hasMoved) return;

			DirectX::XMMATRIX _rotation = DirectX::XMMatrixRotationRollPitchYaw(_pitch, _yaw, 0);
			*_target = DirectX::XMVector3TransformCoord(*_defaultForward, _rotation);
			*_target = DirectX::XMVector3Normalize(*_target);

			DirectX::XMMATRIX tempYRotation = DirectX::XMMatrixRotationY(_yaw);

			*_right = DirectX::XMVector3TransformCoord(*_defaultRight, tempYRotation);
			*_up = DirectX::XMVector3TransformCoord(*_up, tempYRotation);
			*_forward = DirectX::XMVector3TransformCoord(*_defaultForward, tempYRotation);

			DirectX::XMVECTOR temp = DirectX::XMVectorSet(
				_distanceRight * DirectX::XMVectorGetX(*_right),
				_distanceRight * DirectX::XMVectorGetY(*_right),
				_distanceRight * DirectX::XMVectorGetZ(*_right),
				0.0f);
			*_position = DirectX::XMVectorAdd(*_position, temp);

			temp = DirectX::XMVectorSet(
				_distanceForward * DirectX::XMVectorGetX(*_forward),
				_distanceForward * DirectX::XMVectorGetY(*_forward),
				_distanceForward * DirectX::XMVectorGetZ(*_forward),
				0.0f);

			*_position = DirectX::XMVectorAdd(*_position, temp);

			_distanceRight = 0.0f;
			_distanceForward = 0.0f;

			*_target = DirectX::XMVectorAdd(*_position, *_target);
			*_view = DirectX::XMMatrixLookAtLH(*_position, *_target, *_up);
			*_viewProjection = (*_view) * (*_projection);

			_hasMoved = false;
		}

		void Camera::changeFoV(float fov)
		{
			_fov = fov;
			*_projection = DirectX::XMMatrixPerspectiveFovLH(_fov, (float)_width / _height, _nearZ, _farZ);
		}

		void Camera::changeViewport(unsigned int width, unsigned int height)
		{
			_width = width;
			_height = height;
			*_projection = DirectX::XMMatrixPerspectiveFovLH(_fov, (float)_width / _height, _nearZ, _farZ);
		}

		void Camera::changeViewDistance(float nearZ, float farZ)
		{
			_nearZ = nearZ;
			_farZ = farZ;
			*_projection = DirectX::XMMatrixPerspectiveFovLH(_fov, (float)_width / _height, _nearZ, _farZ);
		}

		DirectX::XMMATRIX Camera::getViewProjection()
		{
			return *_viewProjection;
		}

		void Camera::setSensitivity(float movementSensitivity, float rotationSensitivity)
		{
			_movementSensitivity = movementSensitivity;
			_rotationSensitivity = rotationSensitivity;
		}

		void Camera::rotate(float yaw, float pitch)
		{
			_yaw += yaw;
			if (_yaw >= _fullRotation) 
				_yaw -= _fullRotation;
			else if (_yaw <= -_fullRotation) 
				_yaw += _fullRotation;

			_pitch += pitch;
			if (_pitch >= _fullRotation / 4) 
				_pitch = _fullRotation / 4;
			else if (_pitch <= -_fullRotation / 4) 
				_pitch = -_fullRotation / 4;

			_hasMoved = true;
		}

		void Camera::moveForward()
		{
			_distanceForward += _movementSensitivity;
			_hasMoved = true;
		}

		void Camera::moveBackward()
		{
			_distanceForward -= _movementSensitivity;
			_hasMoved = true;
		}

		void Camera::moveLeft()
		{
			_distanceRight -= _movementSensitivity;
			_hasMoved = true;
		}

		void Camera::moveRight()
		{
			_distanceRight += _movementSensitivity;
			_hasMoved = true;
		}
	}
}