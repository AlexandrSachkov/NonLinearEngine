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

#ifndef NLRE_ASSIMP_ASSET_IMPORTER_
#define NLRE_ASSIMP_ASSET_IMPORTER_

#include <assimp\include\Importer.hpp>
#include <assimp\include\scene.h> 
#include <assimp\include\postprocess.h>  

#define AI_CONFIG_PP_SBP_REMOVE aiPrimitiveType_POINT | aiPrimitiveType_LINE

#include "NLREAssetImporterBase.h"
#include "RenderingDevice\NLREStreamSet.h"
#include "RenderingDevice\NLRERenderingDevice.h"
#include "NLRETextureLoader.h"

class NLREAssimpAssetImporter : public virtual NLREAssetImporterBase
{
public:
	NLREAssimpAssetImporter(NLRERenderingDevice* renderingDevice, NLRETextureLoader* textureLoader);
	NLREAssimpAssetImporter(const NLREAssimpAssetImporter& other);
	~NLREAssimpAssetImporter();

	bool importAssets(std::wstring path, std::vector<NLRE_RenderableAsset*>& assets);

private:
	bool initialize();

	std::vector<NLRE_RenderableAsset*> loadAsStatic(const aiScene* scene);

	NLRE_Mesh** loadMeshes(const aiScene* scene);
	void loadGeometryStream(aiMesh* mesh, NLRE_GeomStr*& geomStreamArr, unsigned int& streamLength);
	void loadIndices(aiMesh* mesh, NLRE_Index*& indexArr, unsigned int& length);

	void loadMaterialBuffer(aiMaterial* material, NLRE_MaterialBufferStruct& materialBuffStruct);
	void loadMaterialParams(aiMaterial* material, NLRE_Material*& nlreMaterial);
	void loadMaterialTextures(aiMaterial* material, NLRE_Material*& nlreMaterial);
	NLRE_Material** loadMaterials(const aiScene* scene);

	void nextNode(const aiScene* scene, aiNode* node, aiMatrix4x4& accTransform, NLRE_Mesh** meshArr, NLRE_Material** materialArr, std::vector<NLRE_RenderableAsset*>& assetArr);
	void assembleAsset(const aiScene* scene, unsigned int meshIndex, aiMatrix4x4& transform, NLRE_Mesh** meshArr, NLRE_Material** materialArr, std::vector<NLRE_RenderableAsset*>& assetArr);

	NLRERenderingDevice* _renderingDevice;
	NLRETextureLoader* _textureLoader;
};
#endif