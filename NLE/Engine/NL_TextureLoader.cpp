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

#include "NL_TextureLoader.h"

#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"

namespace NLE
{
	namespace IMPORTER
	{
		bool TextureLoader::loadTexture(
			ID3D11Device* d3dDevice,
			std::wstring path,
			D3D11_BIND_FLAG bindFlag,
			D3D11_USAGE usage,
			ID3D11Texture2D*& texture2D,
			ID3D11ShaderResourceView*& resourceView
			)
		{
			HRESULT hr;
			std::wstring ddsExt(L".dds");
			std::wstring ddsExtCaps(L".DDS");

			if (path.rfind(ddsExt) != std::string::npos || path.rfind(ddsExtCaps) != std::string::npos) {
				hr = DirectX::CreateDDSTextureFromFileEx(
					d3dDevice,
					path.c_str(),
					NULL,
					usage,
					bindFlag,
					NULL,
					NULL,
					false,
					(ID3D11Resource**)&texture2D,
					&resourceView);
			}
			else {
				hr = DirectX::CreateWICTextureFromFileEx(
					d3dDevice,
					path.c_str(),
					NULL,
					usage,
					bindFlag,
					NULL,
					NULL,
					false,
					(ID3D11Resource**)&texture2D,
					&resourceView);
			}

			if (FAILED(hr))
			{
				std::string stringPath(path.begin(), path.end());
				printf("Texture \"%s\" failed to load\n", stringPath.c_str());
				return false;
			}
			return true;
		}
	}
}
