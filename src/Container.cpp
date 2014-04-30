#include "stdafx.h"
#include "Container.h"

Vertex vertexArray[] =
{
	// Front Face
	Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
	Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f),
	Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f),
	Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

	// Back Face
	Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
	Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
	Vertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
	Vertex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f),

	// Top Face
	Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
	Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
	Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
	Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

	// Bottom Face
	Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
	Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
	Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f),
	Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f),

	// Left Face
	Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
	Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
	Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f),
	Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

	// Right Face
	Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
	Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f),
	Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
	Vertex(1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
};

DWORD indices[] = {
	// Front Face
	0, 1, 2,
	0, 2, 3,

	// Back Face
	4, 5, 6,
	4, 6, 7,

	// Top Face
	8, 9, 10,
	8, 10, 11,

	// Bottom Face
	12, 13, 14,
	12, 14, 15,

	// Left Face
	16, 17, 18,
	16, 18, 19,

	// Right Face
	20, 21, 22,
	20, 22, 23
};

Container::Container(NLREDeviceController* deviceController, NLRERenderingDevice* renderingDevice, int width, int height)
{
	if (!deviceController || !renderingDevice)
	{
		throw std::exception("Container failed to initialize: null ptr");
	}
	_deviceController = deviceController;
	_renderingDevice = renderingDevice;

	_texture = NULL;

	mCamView = new NLE_FLOAT4X4();
	mCamProjection = new NLE_FLOAT4X4();
	mObjWorld = new NLE_FLOAT4X4();

	NLE_VECTOR camPosition = NLEMath::NLEVectorSet(0.0f, 3.0f, -20.0f, 0.0f);
	NLE_VECTOR camTarget = NLEMath::NLEVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	NLE_VECTOR camUp = NLEMath::NLEVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	NLE_MATRIX camView = NLEMath::NLEMatrixLookAtLH(camPosition, camTarget, camUp);
	NLEMath::NLEStoreFloat4x4(mCamView, camView);
	
	//Set the Projection matrix
	NLE_MATRIX camProjection = NLEMath::NLEMatrixPerspectiveFovLH(0.4f*3.14f, (float)width / height, 1.0f, 1000.0f);
	NLEMath::NLEStoreFloat4x4(mCamProjection, camProjection);



	NLE_MATRIX objWorld = NLEMath::NLELoadFloat4x4(mObjWorld);

	NLE_MATRIX WVP = objWorld * camView * camProjection;
	NLEMath::NLEStoreFloat4x4(&(cbPerObj.WVP), XMMatrixTranspose(WVP));

	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "Container failed to initialize");
		throw std::exception("Container failed to initialize");
	}
}

Container::~Container()
{

}

bool Container::initialize()
{

	if (!_renderingDevice->createBuffer<Vertex>(NLRE_BIND_SHADER_RESOURCE, NLRE_USAGE_IMMUTABLE, vertexArray, 24, _vertexBuffer)) return false;
	if (!_renderingDevice->createBuffer<DWORD>(NLRE_BIND_SHADER_RESOURCE, NLRE_USAGE_IMMUTABLE, indices, 24, _indexBuffer)) return false;
	if (!_renderingDevice->createBuffer<cbPerObject>(NLRE_BIND_SHADER_RESOURCE, NLRE_USAGE_DYNAMIC, &cbPerObj, 1, _constantBuffer)) return false;
	//if (!_renderingDevice->loadTexture(L"C:\\Users\\Alex\\Desktop\\braynzar.jpg", NLRE_USAGE_IMMUTABLE, NLRE_BIND_SHADER_RESOURCE, NULL, _texture)) return false;
	return true;
}

void Container::render()
{
	_deviceController->render(_vertexBuffer, _indexBuffer, _constantBuffer, _texture);
}