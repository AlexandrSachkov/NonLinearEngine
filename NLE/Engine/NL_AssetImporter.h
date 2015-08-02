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

#ifndef NL_ASSET_IMPORTER_H_
#define NL_ASSET_IMPORTER_H_

#include "NL_RenderingResources.h"

#pragma warning( push )
#pragma warning( disable : 4005)

#define AI_CONFIG_PP_SBP_REMOVE aiPrimitiveType_POINT | aiPrimitiveType_LINE
#include <assimp\Importer.hpp>
#include <assimp\scene.h> 
#include <assimp\postprocess.h>  
#include <assimp\Logger.hpp>
#include <assimp\LogStream.hpp>
#include <assimp\DefaultLogger.hpp>

#pragma warning( pop ) 

#include <d3d11.h>
#include <DirectXMath.h>

#include <string>
#include <vector>
#include <memory>


namespace NLE
{
	namespace IMPORTER
	{
		class TextureLoader;

		class AssimpLogStream : public Assimp::LogStream
		{
		public:
			AssimpLogStream(){};
			~AssimpLogStream(){};

			void write(const char* message)
			{
				printf("Assimp error: %s\n", message);
			}
		};

		class AssetImporter
		{
		public:
			AssetImporter();
			~AssetImporter();

			bool importAssets(
				ID3D11Device* d3dDevice, 
				std::wstring path, 
				std::vector<GRAPHICS::RESOURCES::Renderable>& assets
				);
			void setTextureResourcePath(std::wstring path);

		private:
			void loadAsStatic(
				ID3D11Device* d3dDevice, 
				const aiScene* scene,
				std::vector<GRAPHICS::RESOURCES::Renderable>& assets
				);

			GRAPHICS::RESOURCES::Mesh* loadMeshes(ID3D11Device* d3dDevice, const aiScene* scene);
			void loadVertices(aiMesh* mesh, GRAPHICS::RESOURCES::Vertex*& vertexArr, unsigned int& streamLength);
			void loadIndices(aiMesh* mesh, GRAPHICS::RESOURCES::Index*& indexArr, unsigned int& length);

			void loadMaterialBuffer(aiMaterial* material, GRAPHICS::RESOURCES::MaterialBuffer& materialBuffer);
			void loadMaterialParams(aiMaterial* material, GRAPHICS::RESOURCES::Material& nleMaterial);
			void loadMaterialTextures(ID3D11Device* d3dDevice, aiMaterial* material, GRAPHICS::RESOURCES::Material& nleMaterial);
			GRAPHICS::RESOURCES::Material* loadMaterials(ID3D11Device* d3dDevice, const aiScene* scene);

			void nextNode(
				ID3D11Device* d3dDevice,
				const aiScene* scene,
				aiNode* node,
				aiMatrix4x4 accTransform,
				GRAPHICS::RESOURCES::Mesh* meshArr,
				GRAPHICS::RESOURCES::Material* materialArr,
				std::vector<GRAPHICS::RESOURCES::Renderable>& assetArr
				);

			void assembleAsset(
				ID3D11Device* d3dDevice,
				const aiScene* scene,
				unsigned int meshIndex,
				aiMatrix4x4 transform,
				GRAPHICS::RESOURCES::Mesh* meshArr,
				GRAPHICS::RESOURCES::Material* materialArr,
				std::vector<GRAPHICS::RESOURCES::Renderable>& assetArr
				);

			std::wstring generateTextureResourcePath(aiString textureResourcePath);

			void printFloat4x4(DirectX::XMFLOAT4X4& matrix);
			void printFloat4x4(aiMatrix4x4& matrix);

			std::wstring _textureResourcePath;
		};
	}
}

#endif