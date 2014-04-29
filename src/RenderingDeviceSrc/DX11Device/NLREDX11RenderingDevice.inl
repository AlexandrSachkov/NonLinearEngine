#ifdef NLRE_DX11_RENDERING_DEVICE_

inline void NLREDX11RenderingDevice::setRenderTargets(
	unsigned int numRenderTargets,
	NLRE_APIRenderTargetView* renderTargerViewArr,
	NLRE_APIDepthStencilView* depthStencilView)
{
	_d3d11DevCon->OMSetRenderTargets(numRenderTargets, &renderTargerViewArr, depthStencilView);
}

inline void NLREDX11RenderingDevice::VSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr)
{
	_d3d11DevCon->VSSetShaderResources(startSlot, numViews, &resourceViewArr);
}

inline void NLREDX11RenderingDevice::PSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr)
{
	_d3d11DevCon->PSSetShaderResources(startSlot, numViews, &resourceViewArr);
}

inline void NLREDX11RenderingDevice::GSSetShaderResources(unsigned int startSlot, unsigned int numViews, NLRE_APIShaderResourceView* resourceViewArr)
{
	_d3d11DevCon->GSSetShaderResources(startSlot, numViews, &resourceViewArr);
}

inline void NLREDX11RenderingDevice::setVertexShader(const NLRE_VertexShader& vertexShader)
{
	_d3d11DevCon->VSSetShader(vertexShader.apiVertexShader, NULL, 0);
}

inline void NLREDX11RenderingDevice::setPixelShader(const NLRE_PixelShader& pixelShader)
{
	_d3d11DevCon->PSSetShader(pixelShader.apiPixelShader, NULL, 0);
}

inline void NLREDX11RenderingDevice::setBlendState(NLRE_APIBlendState* blendState, float blendFactor[])
{
	_d3d11DevCon->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

inline void NLREDX11RenderingDevice::VSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer)
{
	_d3d11DevCon->VSSetConstantBuffers(startSlot, numBuffers, &(buffer.apiBuffer));
}

inline void NLREDX11RenderingDevice::PSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer)
{
	_d3d11DevCon->PSSetConstantBuffers(startSlot, numBuffers, &(buffer.apiBuffer));
}

inline void NLREDX11RenderingDevice::GSSetConstantBuffer(unsigned int startSlot, unsigned int numBuffers, const NLRE_Buffer& buffer)
{
	_d3d11DevCon->GSSetConstantBuffers(startSlot, numBuffers, &(buffer.apiBuffer));
}

inline void NLREDX11RenderingDevice::setVertexBuffer(const NLRE_Buffer& buffer, unsigned int slotNum)
{
	_d3d11DevCon->IASetVertexBuffers(slotNum, 1, &(buffer.apiBuffer), &(buffer.elementSize), 0);
}

inline void NLREDX11RenderingDevice::setIndexBuffer(const NLRE_Buffer& buffer)
{
	_d3d11DevCon->IASetIndexBuffer(buffer.apiBuffer, DXGI_FORMAT_R32_UINT, 0);
}

inline void NLREDX11RenderingDevice::setInputLayout(NLRE_APIInputLayout* inputLayout)
{
	_d3d11DevCon->IASetInputLayout(inputLayout);
}

inline void NLREDX11RenderingDevice::setPrimitiveTopology(NLRE_PRIMITIVE_TOPOLOGY primitiveTopology)
{
	_d3d11DevCon->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)primitiveTopology);
}

inline void NLREDX11RenderingDevice::setViewPort(int numViewports, int x, int y, int width, int height, float minDepth, float maxDepth)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = x;
	viewport.TopLeftY = y;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = minDepth;
	viewport.MaxDepth = maxDepth;

	//Set the Viewport
	_d3d11DevCon->RSSetViewports(numViewports, &viewport);
}

inline void NLREDX11RenderingDevice::setViewPort()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = _screenWidth;
	viewport.Height = _screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	//Set the Viewport
	_d3d11DevCon->RSSetViewports(1, &viewport);
}

inline void NLREDX11RenderingDevice::VSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState)
{
	_d3d11DevCon->VSSetSamplers(startSlot, numStates, &samplerState);
}

inline void NLREDX11RenderingDevice::PSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState)
{
	_d3d11DevCon->PSSetSamplers(startSlot, numStates, &samplerState);
}

inline void NLREDX11RenderingDevice::GSSetTextureSamplerState(unsigned int startSlot, unsigned int numStates, NLRE_APISamplerState* samplerState)
{
	_d3d11DevCon->GSSetSamplers(startSlot, numStates, &samplerState);
}

inline void NLREDX11RenderingDevice::setRasterizerState(NLRE_APIRasterizerState* rasterizerState)
{
	_d3d11DevCon->RSSetState(rasterizerState);
}

inline void NLREDX11RenderingDevice::clearRenderTargetView(NLRE_APIRenderTargetView* renderTargetView, float colorRGBA[])
{
	_d3d11DevCon->ClearRenderTargetView(renderTargetView, colorRGBA);
}

inline void NLREDX11RenderingDevice::clearDepthStencilView(NLRE_APIDepthStencilView* depthStencilView)
{
	_d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

inline void NLREDX11RenderingDevice::display()
{
	_swapChain->Present(0, 0);
}

#endif