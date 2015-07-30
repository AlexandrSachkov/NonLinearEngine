/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2015 Alexandr Sachkov

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

#ifndef NL_CAMERA_H_
#define NL_CAMERA_H_

#include <DirectXMath.h>

namespace NLE
{
	namespace GRAPHICS
	{
		class Camera
		{
		public:
			Camera(float x, float y, float z, int width, int height);
			~Camera();

			void changeFoV(float fov);
			void changeViewport(unsigned int width, unsigned int height);
			void changeViewDistance(float nearZ, float farZ);
			DirectX::XMMATRIX getViewProjection();
			void reset();
			void setSensitivity(float movementSensitivity, float rotationSensitivity);
			void update();

			void rotate(float yaw, float pitch);

			void moveForward();
			void moveBackward();
			void moveLeft();
			void moveRight();

		private:
			float _fullRotation;

			float _initXPos;
			float _initYPos;
			float _initZPos;

			float _fov;
			float _nearZ;
			float _farZ;
			unsigned int _width;
			unsigned int _height;

			bool _hasMoved;

			DirectX::XMMATRIX* _viewProjection;
			DirectX::XMMATRIX* _view;
			DirectX::XMMATRIX* _projection;

			DirectX::XMVECTOR* _defaultForward;
			DirectX::XMVECTOR* _defaultRight;

			DirectX::XMVECTOR* _position;
			DirectX::XMVECTOR* _target;
			DirectX::XMVECTOR* _up;

			DirectX::XMVECTOR* _forward;
			DirectX::XMVECTOR* _right;

			float _movementSensitivity;
			float _rotationSensitivity;

			float _distanceForward;
			float _distanceRight;

			float _pitch;
			float _yaw;
		};
	}
}

#endif