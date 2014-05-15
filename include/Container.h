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

#ifndef CONTAINER_
#define CONTAINER_

#include "NLREMain\stdafx.h"
#include "ResourceLoader\NLRETextureLoader.h"
#include "RenderingDevice\NLREDeviceController.h"

struct cbPerObject
{
	NLE_FLOAT4X4  WVP;
};

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float u, float v)
		: pos(x, y, z), texCoord(u, v){}

	NLE_FLOAT3 pos;
	NLE_FLOAT2 texCoord;
};

struct Vertex2
{
	Vertex2(){}
	Vertex2(float x, float y, float z)
		: pos(x, y, z){}

	NLE_FLOAT3 pos;
};

class Container
{
public:
	Container(NLREDeviceController* deviceController, NLRERenderingDevice* renderingDevice, NLRETextureLoader* textureLoader, int width, int height);
	~Container();

	void render();
private:
	bool initialize();

	NLREDeviceController* _deviceController;
	NLRERenderingDevice* _renderingDevice;
	NLRETextureLoader* _textureLoader;

	NLRE_Buffer _vertexBuffer;
	NLRE_Buffer _indexBuffer;
	NLRE_Buffer _constantBuffer;
	NLRE_APITexture2D* _texture2D;
	NLRE_APIShaderResourceView* _texture2DResourceView;

	NLE_FLOAT4X4* mCamView;
	NLE_FLOAT4X4* mCamProjection;
	NLE_FLOAT4X4* mObjWorld;

	cbPerObject cbPerObj;

	std::vector<NLRE_RenderableAsset*> assets;
};

#endif