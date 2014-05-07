#include "stdafx.h"
#include "RenderingDevice\DX11Device\NLREDX11InputLayoutDescriptions.h"

const NLRE_APIInputLayoutDecs NLREDX11InputLayoutDescriptions::forwardPosNormTanTextDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TANGENT", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const NLRE_APIInputLayoutDecs NLREDX11InputLayoutDescriptions::forwardPosTextDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const NLRE_APIInputLayoutDecs NLREDX11InputLayoutDescriptions::forwardPosDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

NLRE_InputLayoutDesc NLREDX11InputLayoutDescriptions::forwardPosNormTanText(forwardPosNormTanTextDesc, ARRAYSIZE(forwardPosNormTanTextDesc));
NLRE_InputLayoutDesc NLREDX11InputLayoutDescriptions::forwardPosText(forwardPosTextDesc, ARRAYSIZE(forwardPosTextDesc));
NLRE_InputLayoutDesc NLREDX11InputLayoutDescriptions::forwardPos(forwardPosDesc, ARRAYSIZE(forwardPosDesc));