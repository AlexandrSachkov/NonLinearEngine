#include "stdafx.h"
#include "RenderingDevice\NLREForwardRT.h"
#include "RenderingDevice\NLREInputLayoutDescriptions.h"

NLREForwardRT::NLREForwardRT(NLRERenderingDevice* renderingDevice)
{
	_renderingDevice = renderingDevice;

	_backBufferRenderTargetView = NULL;
	_noBlendState = NULL;
	_blendState = NULL;
	_depthStencilView = NULL;
	_inputLayout = NULL;
	_backFaceCull = NULL;
	_frontFaceCull = NULL;
	_textureSamplerState = NULL;
	

	if (!initialize())
	{
		NLRE_Log::err(NLRE_Log::CRITICAL, "ForwardRT failed to initialize");
		throw new std::exception("ForwardRT failed to initialize");
	}
}

bool NLREForwardRT::initialize()
{
	if (!_renderingDevice->createBackBufferRenderTargetView(_backBufferRenderTargetView)) return false;
	if (!_renderingDevice->createBlendStates(false, false, 1, false, _noBlendState)) return false;
	if (!_renderingDevice->createBlendStates(true, false, 1, false, _blendState)) return false;
	if (!_renderingDevice->createDepthStencilView(_depthStencilView)) return false;
	if (!_renderingDevice->loadVertexShader(L"Shaders\Forward_PosText_VS.hlsl", _vertexShader)) return false;
	if (!_renderingDevice->createInputLayout(forwardPosText, _vertexShader, _inputLayout)) return false;
	if (!_renderingDevice->createRasterizerState(NLRE_CULL_BACK, NLRE_FILL_SOLID, _backFaceCull)) return false;
	if (!_renderingDevice->createRasterizerState(NLRE_CULL_FRONT, NLRE_FILL_SOLID, _backFaceCull)) return false;
	if (!_renderingDevice->createTextureSamplerState(_textureSamplerState)) return false;
	if (!_renderingDevice->loadPixelShader(L"Shaders\Forward_PosText_PS.hlsl", _pixelShader)) return false;
	
	_renderingDevice->setRenderTargets(1, _backBufferRenderTargetView, _depthStencilView);
	_renderingDevice->setVertexShader(_vertexShader);
	_renderingDevice->setPixelShader(_pixelShader);
	_renderingDevice->setInputLayout(_inputLayout);
	_renderingDevice->setPrimitiveTopology(NLRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_renderingDevice->setViewPort();

	return true;
}

NLREForwardRT::NLREForwardRT(const NLREForwardRT& other)
{
}

NLREForwardRT::~NLREForwardRT()
{

}

void NLREForwardRT::render()
{

}

