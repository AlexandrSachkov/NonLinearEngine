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

#ifndef NLRE_ASSIMP_ASSET_IMPORTER_
#define NLRE_ASSIMP_ASSET_IMPORTER_

#include <assimp\include\Importer.hpp>
#include <assimp\include\scene.h> 
#include <assimp\include\postprocess.h>  
#include <assimp\include\Logger.hpp>
#include <assimp\include\LogStream.hpp>
#include <assimp\include\DefaultLogger.hpp>

#define AI_CONFIG_PP_SBP_REMOVE aiPrimitiveType_POINT | aiPrimitiveType_LINE

#include "RenderingEngine\ResourceLoader\NLREAssetImporter.h"
#include "RenderingEngine\RenderingDevice\NLREStreamSet.h"
#include "RenderingEngine\RenderingDevice\NLRERenderingDevice.h"
#include "RenderingEngine\ResourceLoader\NLRETextureLoader.h"

class NLREAssimpLogStream : public Assimp::LogStream
{
public:
	NLREAssimpLogStream(){};
	~NLREAssimpLogStream(){};

	void write(const char* message)
	{
		NLRE_Log::console(message);
	}
};

class NLREAssimpAssetImporter : public virtual NLREAssetImporter
{
public:
	NLREAssimpAssetImporter(
		std::shared_ptr<NLRERenderingDevice> renderingDevice, 
		std::shared_ptr<NLRETextureLoader> textureLoader);
	NLREAssimpAssetImporter(const NLREAssimpAssetImporter& other);
	~NLREAssimpAssetImporter();

	bool importAssets(std::wstring path, std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assets);
	void setTextureResourcePath(std::wstring path);
	void enableBuiltInTexturePath(bool status);

private:
	bool initialize();

	std::vector<std::shared_ptr<NLRE_RenderableAsset>> loadAsStatic(std::string path, const aiScene* scene);

	std::shared_ptr<NLRE_Mesh>* loadMeshes(const aiScene* scene);
	void loadGeometryStream(aiMesh* mesh, NLRE_GeomStr*& geomStreamArr, unsigned int& streamLength);
	void loadIndices(aiMesh* mesh, NLRE_Index*& indexArr, unsigned int& length);

	void loadMaterialBuffer(aiMaterial* material, NLRE_MaterialBufferStruct& materialBuffStruct);
	void loadMaterialParams(aiMaterial* material, std::shared_ptr<NLRE_Material>& nlreMaterial);
	void loadMaterialTextures(std::string path, aiMaterial* material, std::shared_ptr<NLRE_Material>& nlreMaterial);
	std::shared_ptr<NLRE_Material>* loadMaterials(std::string path, const aiScene* scene);

	void nextNode(
		const aiScene* scene, 
		aiNode* node, 
		aiMatrix4x4 accTransform, 
		std::shared_ptr<NLRE_Mesh>* meshArr,
		std::shared_ptr<NLRE_Material>* materialArr,
		std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assetArr,
		int level);

	void assembleAsset(
		const aiScene* scene, 
		unsigned int meshIndex, 
		aiMatrix4x4 transform, 
		std::shared_ptr<NLRE_Mesh>* meshArr,
		std::shared_ptr<NLRE_Material>* materialArr,
		std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assetArr,
		int level);

	std::wstring generateTextureResourcePath(aiString textureResourcePath, std::string assetPath);

	void printFloat4x4(NLE_FLOAT4X4& matrix);
	void printFloat4x4(aiMatrix4x4& matrix);

	std::shared_ptr<NLRERenderingDevice> _renderingDevice;
	std::shared_ptr<NLRETextureLoader> _textureLoader;
	std::wstring _textureResourcePath;
	bool useBuiltInTexturePath;
};
#endif