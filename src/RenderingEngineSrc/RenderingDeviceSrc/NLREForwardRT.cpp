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
#include "RenderingEngine\RenderingDevice\NLREForwardRT.h"

NLREForwardRT::NLREForwardRT(std::shared_ptr<NLRERenderingDevice> renderingDevice)
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
		throw std::exception("ForwardRT failed to initialize");
	}
	
}

bool NLREForwardRT::initialize()
{
	if (!_renderingDevice->createBackBufferRenderTargetView(_backBufferRenderTargetView)) return false;
	if (!_renderingDevice->createBlendStates(false, false, 1, false, _noBlendState)) return false;
	if (!_renderingDevice->createBlendStates(true, false, 1, false, _blendState)) return false;
	if (!_renderingDevice->createDepthStencilView(_depthStencilView)) return false;
	if (!_renderingDevice->loadVertexShader(L"Shaders\\Forward_PosNormText_VS.cso", _vertexShader)) return false;
	if (!_renderingDevice->createInputLayout(NLREInputLayoutDescriptions::forwardPosNormText, _vertexShader, _inputLayout)) return false;
	if (!_renderingDevice->createRasterizerState(NLRE_CULL_BACK, NLRE_FILL_SOLID, _backFaceCull)) return false;
	if (!_renderingDevice->createRasterizerState(NLRE_CULL_FRONT, NLRE_FILL_SOLID, _frontFaceCull)) return false;
	if (!_renderingDevice->createTextureSamplerState(_textureSamplerState)) return false;
	if (!_renderingDevice->loadPixelShader(L"Shaders\\Forward_PosNormText_PS.cso", _pixelShader)) return false;
	
	_renderingDevice->setRenderTargets(1, _backBufferRenderTargetView, _depthStencilView);
	_renderingDevice->setVertexShader(_vertexShader);
	_renderingDevice->setPixelShader(_pixelShader);
	_renderingDevice->setInputLayout(_inputLayout);
	_renderingDevice->setPrimitiveTopology(NLRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_renderingDevice->setViewPort();

	_renderingDevice->PSSetTextureSamplerState(0, 1, _textureSamplerState);
	_renderingDevice->setRasterizerState(_backFaceCull);
	
	return true;
}

NLREForwardRT::NLREForwardRT(const NLREForwardRT& other)
{
}

NLREForwardRT::~NLREForwardRT()
{
	if (_backBufferRenderTargetView) _backBufferRenderTargetView->Release();
	if (_noBlendState) _noBlendState->Release();
	if (_blendState) _blendState->Release();
	if (_depthStencilView) _depthStencilView->Release();
	if (_inputLayout) _inputLayout->Release();
	if (_backFaceCull) _backFaceCull->Release();
	if (_frontFaceCull) _frontFaceCull->Release();
	if (_textureSamplerState) _textureSamplerState->Release();
}

void NLREForwardRT::render(std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assets)
{
	float bgColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	_renderingDevice->clearRenderTargetView(_backBufferRenderTargetView, bgColor);
	_renderingDevice->clearDepthStencilView(_depthStencilView);

	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };

	int counter = 0;
	for (std::vector<std::shared_ptr<NLRE_RenderableAsset>>::iterator it = assets.begin(); it != assets.end(); ++it)
	{
		//if (counter == 2) break;

		std::shared_ptr<NLRE_RenderableAsset> asset = *it;
		if (asset->mesh->geomBuffer.apiBuffer)
		{
			_renderingDevice->setVertexBuffer(asset->mesh->geomBuffer, 0);
		}
		
		if (asset->mesh->indexBuffer.apiBuffer)
		{
			_renderingDevice->setIndexBuffer(asset->mesh->indexBuffer);
		}
		if (asset->transformationBuffer.apiBuffer)
		{
			_renderingDevice->VSSetConstantBuffer(0, 1, asset->transformationBuffer);
		}
		if (asset->material->diffuseTextView)
		{
			_renderingDevice->PSSetShaderResources(0, 1, asset->material->diffuseTextView);
		}
		_renderingDevice->drawIndexed(asset->mesh->indexBuffer);
		counter++;
	}
}

