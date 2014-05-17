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

#ifndef NLRE_CAMERA_
#define NLRE_CAMERA_

class NLRECamera
{
public:
	NLRECamera(float x, float y, float z, int width, int height);
	NLRECamera(const NLRECamera& other);
	~NLRECamera();

	void reset();

	void pitchUp();
	void pitchDOwn();
	void yawLeft();
	void yawRight();

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	bool hasMoved();
	void setSensitivity(float movementSensitivity, float rotationSensitivity);

private:
	NLE_FLOAT4X4 _viewProjection;
	NLE_FLOAT4X4 _view;
	NLE_FLOAT4X4 _projection;

	NLE_FLOAT4 _defaultForward;
	NLE_FLOAT4 _defaultRight;
	NLE_FLOAT4 _defaultUp;

	NLE_FLOAT4 _forward;
	NLE_FLOAT4 _right;
	NLE_FLOAT4 _up;

	float _movementSensitivity;
	float _rotationSensitivity;

	float _distanceForward;
	float _distanceRight;
	float _distanceUp;

	float _pitch;
	float _yaw;
};

#endif