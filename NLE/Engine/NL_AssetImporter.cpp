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

#include "NL_AssetImporter.h"
#include "NL_TextureLoader.h"
#include "NL_D3D11Utility.h"
#include "NL_GScene.h"

#include <locale>
#include <codecvt>
#include <string>
#include <cstdio>

namespace NLE
{
	namespace IMPORTER
	{
		AssetImporter::AssetImporter() :
			_textureResourcePath(L"")
		{
#if defined(_DEBUG) || defined(DEBUG)
			Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
			const unsigned int severity = Assimp::Logger::Debugging | Assimp::Logger::Info | Assimp::Logger::Err | Assimp::Logger::Warn;
#else
			Assimp::DefaultLogger::create("", Assimp::Logger::NORMAL);
			const unsigned int severity = Assimp::Logger::Err | Assimp::Logger::Warn;
#endif
			Assimp::DefaultLogger::get()->attachStream(new AssimpLogStream(), severity);

			printf("Asset importer created");
		}

		AssetImporter::~AssetImporter()
		{
			Assimp::DefaultLogger::kill();
		}

		void AssetImporter::importScene(
			ID3D11Device* d3dDevice,
			std::wstring& path,
			GRAPHICS::Scene& outScene
			)
		{
			Assimp::Importer importer;
			std::string assetPath(path.begin(), path.end());
			const aiScene* scene = importer.ReadFile(assetPath.c_str(),
				aiProcess_ConvertToLeftHanded |
				aiProcess_CalcTangentSpace |
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_FlipWindingOrder |
				aiProcess_GenUVCoords |
				aiProcess_GenSmoothNormals |
				aiProcess_SortByPType);

			if (!scene)
			{
				printf("Failed to import asset: %s", assetPath.c_str());
			}

			GRAPHICS::RESOURCES::Mesh* meshArr = loadMeshes(d3dDevice, scene);
			GRAPHICS::RESOURCES::Material* materialArr = loadMaterials(d3dDevice, scene);

			nextNode(d3dDevice, scene, scene->mRootNode, scene->mRootNode->mTransformation, meshArr, materialArr, outScene);

			loadLights(d3dDevice, outScene, scene);

			delete[] meshArr;
			delete[] materialArr;
		}

		void AssetImporter::nextNode(
			ID3D11Device* d3dDevice,
			const aiScene* scene,
			aiNode* node,
			aiMatrix4x4 accTransform,
			GRAPHICS::RESOURCES::Mesh* meshArr,
			GRAPHICS::RESOURCES::Material* materialArr,
			GRAPHICS::Scene& outScene)
		{
			aiMatrix4x4 transform;
			if (node->mNumMeshes > 0)
			{
				for (uint_fast32_t i = 0; i < node->mNumMeshes; ++i)
				{
					assembleAsset(d3dDevice, scene, node->mMeshes[i], accTransform, meshArr, materialArr, outScene);
				}
			}

			for (uint_fast32_t i = 0; i < node->mNumChildren; ++i)
			{
				transform = accTransform * node->mChildren[i]->mTransformation;
				nextNode(d3dDevice, scene, node->mChildren[i], transform, meshArr, materialArr, outScene);
			}
		}

		void AssetImporter::assembleAsset(
			ID3D11Device* d3dDevice,
			const aiScene* scene,
			unsigned int meshIndex,
			aiMatrix4x4 transform,
			GRAPHICS::RESOURCES::Mesh* meshArr,
			GRAPHICS::RESOURCES::Material* materialArr,
			GRAPHICS::Scene& outScene
			)
		{
			GRAPHICS::RESOURCES::Renderable asset;
			asset.mesh = meshArr[meshIndex];
			asset.material = materialArr[scene->mMeshes[meshIndex]->mMaterialIndex];

			asset.transformation = DirectX::XMFLOAT4X4((const float*)(&transform.Transpose()));
			GRAPHICS::D3D11Utility::createBuffer<DirectX::XMFLOAT4X4>(
				d3dDevice, 
				D3D11_BIND_CONSTANT_BUFFER, 
				D3D11_USAGE_DYNAMIC, 
				&asset.transformation,
				1, 
				asset.transformationBuffer
				);

			outScene.addStaticRenderable(asset);
		}

		GRAPHICS::RESOURCES::Mesh* AssetImporter::loadMeshes(ID3D11Device* d3dDevice, const aiScene* scene)
		{
			if (!scene->HasMeshes()) return nullptr;

			GRAPHICS::RESOURCES::Mesh* meshArr = new GRAPHICS::RESOURCES::Mesh[scene->mNumMeshes];
			for (uint_fast32_t i = 0; i < scene->mNumMeshes; ++i)
			{
				GRAPHICS::RESOURCES::Vertex* vertexArr = nullptr;
				unsigned int geomStreamLength = 0;
				loadVertices(scene->mMeshes[i], vertexArr, geomStreamLength);
				GRAPHICS::D3D11Utility::createBuffer<GRAPHICS::RESOURCES::Vertex>(d3dDevice, D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_IMMUTABLE, vertexArr, geomStreamLength, meshArr[i].geomBuffer);

				GRAPHICS::RESOURCES::Index* indexArr = nullptr;
				unsigned int indexArrLength = 0;
				D3D_PRIMITIVE_TOPOLOGY primitiveTopology;
				loadIndices(scene->mMeshes[i], indexArr, indexArrLength, primitiveTopology);
				meshArr[i].primitiveTopology = primitiveTopology;
				GRAPHICS::D3D11Utility::createBuffer<GRAPHICS::RESOURCES::Index>(d3dDevice, D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_IMMUTABLE, indexArr, indexArrLength, meshArr[i].indexBuffer);
			}

			return meshArr;
		}

		void AssetImporter::loadVertices(aiMesh* mesh, GRAPHICS::RESOURCES::Vertex*& vertexArr, unsigned int& streamLength)
		{
			if (!mesh->HasPositions()) return;

			streamLength = mesh->mNumVertices;
			vertexArr = new GRAPHICS::RESOURCES::Vertex[streamLength];
			for (uint_fast32_t i = 0; i < streamLength; ++i)
			{
				const aiVector3D* pos = &(mesh->mVertices[i]);
				const aiVector3D* normal = &(mesh->mNormals[i]);
				const aiVector3D* texCoord = &(mesh->mTextureCoords[0][i]);

				vertexArr[i].position = DirectX::XMFLOAT3(pos->x, pos->y, pos->z);
				if (mesh->HasNormals())
				{
					vertexArr[i].normal = DirectX::XMFLOAT3(normal->x, normal->y, normal->z);
				}
				if (mesh->HasTextureCoords(0))
				{
					vertexArr[i].textCoord = DirectX::XMFLOAT2(texCoord->x, texCoord->y);
				}
			}
		}

		void AssetImporter::loadIndices(aiMesh* mesh, GRAPHICS::RESOURCES::Index*& indexArr, unsigned int& indexArrLength, D3D_PRIMITIVE_TOPOLOGY& primitiveTopology)
		{
			if (!mesh->HasFaces()) 
				return;

			uint_fast32_t counter = 0;
			uint_fast32_t numIndices = 0;
			for (uint_fast32_t k = 0; k < mesh->mNumFaces; ++k)
			{
				if (k == 0)
				{
					numIndices = mesh->mFaces[0].mNumIndices;
					indexArrLength = mesh->mNumFaces * numIndices;
					indexArr = new GRAPHICS::RESOURCES::Index[indexArrLength];
					switch (numIndices)
					{
					case 1:
						primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
						break;
					case 2:
						primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
						break;
					case 3:
						primitiveTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
						break;
					default:
						assert(false);
					}
				}
				const aiFace& tempFace = mesh->mFaces[k];
				for (uint_fast32_t m = 0; m < numIndices; m++)
				{
					indexArr[counter] = tempFace.mIndices[m];
					counter++;
				}
			}
		}

		GRAPHICS::RESOURCES::Material* AssetImporter::loadMaterials(ID3D11Device* d3dDevice, const aiScene* scene)
		{
			if (!scene->HasMaterials()) return nullptr;

			GRAPHICS::RESOURCES::Material* materialArr = new GRAPHICS::RESOURCES::Material[scene->mNumMaterials];
			for (uint_fast32_t i = 0; i < scene->mNumMaterials; ++i)
			{
				GRAPHICS::RESOURCES::MaterialBuffer materialBuff;
				loadMaterialBuffer(scene->mMaterials[i], materialBuff);
				GRAPHICS::D3D11Utility::createBuffer<GRAPHICS::RESOURCES::MaterialBuffer>(d3dDevice, D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_IMMUTABLE, &materialBuff, 1, materialArr[i].materialBuffer);

				loadMaterialParams(scene->mMaterials[i], materialArr[i]);
				loadMaterialTextures(d3dDevice, scene->mMaterials[i], materialArr[i]);
			}
			return materialArr;
		}

		void AssetImporter::loadMaterialParams(aiMaterial* material, GRAPHICS::RESOURCES::Material& nleMaterial)
		{
			material->Get(AI_MATKEY_TWOSIDED, nleMaterial.twoSided);

			int temp = 0;

			if (material->Get(AI_MATKEY_BLEND_FUNC, temp) == AI_SUCCESS)				nleMaterial.blendMode = temp;
			if (material->Get(AI_MATKEY_SHADING_MODEL, temp) == AI_SUCCESS)				nleMaterial.shadingModel = temp;
			if (material->Get(AI_MATKEY_MAPPINGMODE_U_DIFFUSE(0), temp) == AI_SUCCESS)	nleMaterial.textureMappingMode_u = temp;
			if (material->Get(AI_MATKEY_MAPPINGMODE_V_DIFFUSE(0), temp) == AI_SUCCESS)	nleMaterial.textureMappingMode_v = temp;
		}

		void AssetImporter::loadMaterialBuffer(aiMaterial* material, GRAPHICS::RESOURCES::MaterialBuffer& materialStruct)
		{
			aiColor3D tempColor;
			if (material->Get(AI_MATKEY_COLOR_DIFFUSE, tempColor) == AI_SUCCESS)
			{
				materialStruct.diffuseColor.x = tempColor.r;
				materialStruct.diffuseColor.y = tempColor.g;
				materialStruct.diffuseColor.z = tempColor.b;
			}
			if (material->Get(AI_MATKEY_COLOR_AMBIENT, tempColor) == AI_SUCCESS)
			{
				materialStruct.ambientColor.x = tempColor.r;
				materialStruct.ambientColor.y = tempColor.g;
				materialStruct.ambientColor.z = tempColor.b;
			}
			if (material->Get(AI_MATKEY_COLOR_SPECULAR, tempColor) == AI_SUCCESS)
			{
				materialStruct.specularColor.x = tempColor.r;
				materialStruct.specularColor.y = tempColor.g;
				materialStruct.specularColor.z = tempColor.b;
			}
			if (material->Get(AI_MATKEY_COLOR_EMISSIVE, tempColor) == AI_SUCCESS)
			{
				materialStruct.emissiveColor.x = tempColor.r;
				materialStruct.emissiveColor.y = tempColor.g;
				materialStruct.emissiveColor.z = tempColor.b;
			}
			if (material->Get(AI_MATKEY_COLOR_TRANSPARENT, tempColor) == AI_SUCCESS)
			{
				materialStruct.transparentColor.x = tempColor.r;
				materialStruct.transparentColor.y = tempColor.g;
				materialStruct.transparentColor.z = tempColor.b;
			}

			float temp = 0.0f;
			if (material->Get(AI_MATKEY_OPACITY, temp) == AI_SUCCESS)			materialStruct.opacity = temp;
			if (material->Get(AI_MATKEY_SHININESS, temp) == AI_SUCCESS)			materialStruct.shininess = temp;
			if (material->Get(AI_MATKEY_SHININESS_STRENGTH, temp) == AI_SUCCESS) materialStruct.shininess_str = temp;
			if (material->Get(AI_MATKEY_REFRACTI, temp) == AI_SUCCESS)			materialStruct.refracti = temp;
		}

		void AssetImporter::loadMaterialTextures(ID3D11Device* d3dDevice, aiMaterial* material, GRAPHICS::RESOURCES::Material& nleMaterial)
		{
			aiString path;

			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0
				&& material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.diffuseText,
					nleMaterial.diffuseTextView);
			}

			if (material->GetTextureCount(aiTextureType_SPECULAR) > 0
				&& material->GetTexture(aiTextureType_SPECULAR, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.specularText,
					nleMaterial.specularTextView);
			}

			if (material->GetTextureCount(aiTextureType_AMBIENT) > 0
				&& material->GetTexture(aiTextureType_AMBIENT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.ambientText,
					nleMaterial.ambientTextView);
			}

			if (material->GetTextureCount(aiTextureType_EMISSIVE) > 0
				&& material->GetTexture(aiTextureType_EMISSIVE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.emissiveText,
					nleMaterial.emissiveTextView);
			}

			if (material->GetTextureCount(aiTextureType_HEIGHT) > 0
				&& material->GetTexture(aiTextureType_HEIGHT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.heightmapText,
					nleMaterial.heightmapTextView);
			}

			if (material->GetTextureCount(aiTextureType_NORMALS) > 0
				&& material->GetTexture(aiTextureType_NORMALS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.normalText,
					nleMaterial.normalTextView);
			}

			if (material->GetTextureCount(aiTextureType_SHININESS) > 0
				&& material->GetTexture(aiTextureType_SHININESS, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.shininessText,
					nleMaterial.shininessTextView);
			}

			if (material->GetTextureCount(aiTextureType_OPACITY) > 0
				&& material->GetTexture(aiTextureType_OPACITY, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.opacityText,
					nleMaterial.opacityTextView);
				printf("Opacity texture\n");
			}

			if (material->GetTextureCount(aiTextureType_DISPLACEMENT) > 0
				&& material->GetTexture(aiTextureType_DISPLACEMENT, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.displacementText,
					nleMaterial.displacementTextView);
			}

			if (material->GetTextureCount(aiTextureType_LIGHTMAP) > 0
				&& material->GetTexture(aiTextureType_LIGHTMAP, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.lightmapText,
					nleMaterial.lightmapTextView);
			}

			if (material->GetTextureCount(aiTextureType_REFLECTION) > 0
				&& material->GetTexture(aiTextureType_REFLECTION, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
			{
				TextureLoader::loadTexture(
					d3dDevice,
					generateTextureResourcePath(path),
					D3D11_BIND_SHADER_RESOURCE,
					D3D11_USAGE_IMMUTABLE,
					nleMaterial.reflectionText,
					nleMaterial.reflectionTextView);
			}
		}

		void AssetImporter::loadLights(ID3D11Device* d3dDevice, GRAPHICS::Scene& outScene, const aiScene* scene)
		{
			printf("Number of lights: %i\n", scene->mNumLights);
			for (uint_fast32_t i = 0; i < scene->mNumLights; ++i)
			{
				switch (scene->mLights[i]->mType)
				{
				case aiLightSource_DIRECTIONAL:
					printf("Directional Light\n");
					//light.type = GRAPHICS::LIGHT_TYPE::DIRECTIONAL;
					break;
				case aiLightSource_POINT:
					printf("Point Light\n");
					//light.type = GRAPHICS::LIGHT_TYPE::POINT;
					break;
				case aiLightSource_SPOT:
					printf("Spot Light\n");
					//light.type = GRAPHICS::LIGHT_TYPE::SPOT;
					break;
				default:
					assert(false);
				}
			}
		}

		void AssetImporter::setTextureResourcePath(std::wstring path)
		{
			_textureResourcePath = path;
		}

		std::wstring AssetImporter::generateTextureResourcePath(aiString textureResourcePath)
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			return converter.from_bytes(textureResourcePath.data);
		}

		void AssetImporter::printFloat4x4(DirectX::XMFLOAT4X4& matrix)
		{
			printf("%f %f %f %f\n", matrix._11, matrix._12, matrix._13, matrix._14);
			printf("%f %f %f %f\n", matrix._21, matrix._22, matrix._23, matrix._24);
			printf("%f %f %f %f\n", matrix._31, matrix._32, matrix._33, matrix._34);
			printf("%f %f %f %f\n\n", matrix._41, matrix._42, matrix._43, matrix._44);
		}

		void AssetImporter::printFloat4x4(aiMatrix4x4& matrix)
		{
			printf("%f %f %f %f\n", matrix.a1, matrix.a2, matrix.a3, matrix.a4);
			printf("%f %f %f %f\n", matrix.b1, matrix.b2, matrix.b3, matrix.b4);
			printf("%f %f %f %f\n", matrix.c1, matrix.c2, matrix.c3, matrix.c4);
			printf("%f %f %f %f\n\n", matrix.d1, matrix.d2, matrix.d3, matrix.d4);
		}
	}
}

