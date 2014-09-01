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

#ifndef NLRE_CAMERA_
#define NLRE_CAMERA_

class NLRECamera
{
public:
	NLRECamera(float x, float y, float z, int width, int height);
	~NLRECamera();

	void changeFoV(float fov);
	void changeViewport(unsigned int width, unsigned int height);
	void changeViewDistance(float nearZ, float farZ);
	NLE_MATRIX getViewProjection();
	void reset();
	void setSensitivity(float movementSensitivity, float rotationSensitivity);
	void update();

	void rotate(float yaw, float pitch);

	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();

private:
	NLRECamera(const NLRECamera& other){}

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

	NLE_MATRIX* _viewProjection;
	NLE_MATRIX* _view;
	NLE_MATRIX* _projection;

	NLE_VECTOR* _defaultForward;
	NLE_VECTOR* _defaultRight;

	NLE_VECTOR* _position;
	NLE_VECTOR* _target;
	NLE_VECTOR* _up;

	NLE_VECTOR* _forward;
	NLE_VECTOR* _right;
	
	float _movementSensitivity;
	float _rotationSensitivity;

	float _distanceForward;
	float _distanceRight;

	float _pitch;
	float _yaw;
};

#endif