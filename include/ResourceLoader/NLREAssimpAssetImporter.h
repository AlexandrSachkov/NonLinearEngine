#ifndef NLRE_ASSIMP_ASSET_IMPORTER_
#define NLRE_ASSIMP_ASSET_IMPORTER_

#include <assimp\include\Importer.hpp>
#include <assimp\include\scene.h> 
#include <assimp\include\postprocess.h>  

#define AI_CONFIG_PP_SBP_REMOVE aiPrimitiveType_POINT | aiPrimitiveType_LINE

#include "NLREAssetImporter.h"
#include "RenderingDevice\NLREStreamSet.h"
#include "RenderingDevice\NLRERenderingDevice.h"
#include "NLRETextureLoader.h"

class NLREAssimpAssetImporter : public virtual NLREAssetImporter
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
	NLRE_Material** loadMaterials(const aiScene* scene);

	void nextNode(const aiScene* scene,aiNode* node, aiMatrix4x4& accTransform, std::vector<NLRE_Mesh*>& meshes);
	void addMesh(const aiScene* scene, unsigned int meshIndex, aiMatrix4x4& transform, std::vector<NLRE_Mesh*>& meshes);

	NLRERenderingDevice* _renderingDevice;
	NLRETextureLoader* _textureLoader;
};
#endif