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
#ifndef NL_D3D11_RENDERING_RESOURCES_H_
#define NL_D3D11_RENDERING_RESOURCES_H_

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#include <memory>
#include <cstdint>

namespace NLE
{
	namespace GRAPHICS
	{
		enum RENDERING_TECHNIQUE
		{
			FORWARD
		};

		enum SHADING_MODEL
		{
			FLAT,
			GOURAUD,
			PHONG,
			BLINN
		};

		enum BLENDING_MODE
		{
			DEFAULT,
			ADDITIVE,
			NONE
		};

		enum LIGHT_TYPE
		{
			DIRECTIONAL,
			POINT,
			SPOT
		};

		namespace RESOURCES
		{

#define SAFE_RELEASE( resource )\
if (resource)					\
{								\
	resource->Release();		\
	resource = nullptr;			\
}								

			struct Vertex
			{
				Vertex() :
					position(0.0f, 0.0f, 0.0f), 
					normal(0.0f, 0.0f, 0.0f), 
					textCoord(0.0f, 0.0f)
				{
				}

				DirectX::XMFLOAT3 position;
				DirectX::XMFLOAT3 normal;
				DirectX::XMFLOAT2 textCoord;
			};

			typedef unsigned long Index;

			struct Buffer
			{
				Buffer() :
					apiBuffer(nullptr),
					usage(D3D11_USAGE::D3D11_USAGE_DEFAULT),
					elementSize(0),
					numberElements(0)
				{
				}

				void release()
				{
					SAFE_RELEASE(apiBuffer);
				}

				ID3D11Buffer* apiBuffer;
				D3D11_BIND_FLAG bindFlag;
				D3D11_USAGE usage;
				uint_fast32_t elementSize;
				uint_fast32_t numberElements;
			};

			struct VertexShader
			{
				VertexShader() :
					apiVertexShader(nullptr),
					blob(nullptr)
				{
				}

				void release()
				{
					SAFE_RELEASE(apiVertexShader);
					SAFE_RELEASE(blob);
				}

				ID3D11VertexShader* apiVertexShader;
				ID3DBlob* blob;
			};

			struct PixelShader
			{
				PixelShader() :
					apiPixelShader(nullptr),
					blob(nullptr)
				{
				}

				void release()
				{
					SAFE_RELEASE(apiPixelShader);
					SAFE_RELEASE(blob);
				}

				ID3D11PixelShader* apiPixelShader;
				ID3DBlob* blob;
			};

			struct Mesh
			{
				void release()
				{
					geomBuffer.release();
					indexBuffer.release();
				}
				Buffer geomBuffer;
				Buffer indexBuffer;
				D3D_PRIMITIVE_TOPOLOGY primitiveTopology;
			};

			__declspec(align(16))
			struct MaterialBuffer
			{
				MaterialBuffer() :
					diffuseColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)),
					ambientColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)),
					specularColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)),
					emissiveColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)),
					transparentColor(DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)),
					opacity(1.0f),
					shininess(0.0f),
					shininess_str(0.0f),
					refracti(0.0f)
				{
				}

				DirectX::XMFLOAT4 diffuseColor;
				DirectX::XMFLOAT4 ambientColor;
				DirectX::XMFLOAT4 specularColor;
				DirectX::XMFLOAT4 emissiveColor;
				DirectX::XMFLOAT4 transparentColor;

				float opacity;
				float shininess;
				float shininess_str;
				float refracti;
			};

			struct Material
			{
				Material() :
					wireframe(false),
					twoSided(false),
					blendMode(BLENDING_MODE::NONE),
					shadingModel(SHADING_MODEL::PHONG),
					textureMappingMode_u(D3D11_TEXTURE_ADDRESS_WRAP),
					textureMappingMode_v(D3D11_TEXTURE_ADDRESS_WRAP),

					diffuseText(nullptr),
					specularText(nullptr),
					ambientText(nullptr),
					emissiveText(nullptr),
					heightmapText(nullptr),
					normalText(nullptr),
					shininessText(nullptr),
					opacityText(nullptr),
					displacementText(nullptr),
					lightmapText(nullptr),
					reflectionText(nullptr),

					diffuseTextView(nullptr),
					specularTextView(nullptr),
					ambientTextView(nullptr),
					emissiveTextView(nullptr),
					heightmapTextView(nullptr),
					normalTextView(nullptr),
					shininessTextView(nullptr),
					opacityTextView(nullptr),
					displacementTextView(nullptr),
					lightmapTextView(nullptr),
					reflectionTextView(nullptr)
				{
				}

				void release()
				{
					SAFE_RELEASE(diffuseText);
					SAFE_RELEASE(specularText);
					SAFE_RELEASE(ambientText);
					SAFE_RELEASE(emissiveText);
					SAFE_RELEASE(heightmapText);
					SAFE_RELEASE(normalText);
					SAFE_RELEASE(shininessText);
					SAFE_RELEASE(opacityText);
					SAFE_RELEASE(displacementText);
					SAFE_RELEASE(lightmapText);
					SAFE_RELEASE(reflectionText);

					SAFE_RELEASE(diffuseTextView);
					SAFE_RELEASE(specularTextView);
					SAFE_RELEASE(ambientTextView);
					SAFE_RELEASE(emissiveTextView);
					SAFE_RELEASE(heightmapTextView);
					SAFE_RELEASE(normalTextView);
					SAFE_RELEASE(shininessTextView);
					SAFE_RELEASE(opacityTextView);
					SAFE_RELEASE(displacementTextView);
					SAFE_RELEASE(lightmapTextView);
					SAFE_RELEASE(reflectionTextView);
				}

				Buffer materialBuffer;

				bool wireframe;
				bool twoSided;
				int blendMode;	//0 = Default:    SourceColor*SourceAlpha + DestColor*(1-SourceAlpha),   1 = Additive:  SourceColor*1 + DestColor*1
				int shadingModel;
				int textureMappingMode_u;
				int textureMappingMode_v;

				ID3D11Texture2D* diffuseText;
				ID3D11Texture2D* specularText;
				ID3D11Texture2D* ambientText;
				ID3D11Texture2D* emissiveText;
				ID3D11Texture2D* heightmapText;
				ID3D11Texture2D* normalText;
				ID3D11Texture2D* shininessText;
				ID3D11Texture2D* opacityText;
				ID3D11Texture2D* displacementText;
				ID3D11Texture2D* lightmapText;
				ID3D11Texture2D* reflectionText;

				ID3D11ShaderResourceView* diffuseTextView;
				ID3D11ShaderResourceView* specularTextView;
				ID3D11ShaderResourceView* ambientTextView;
				ID3D11ShaderResourceView* emissiveTextView;
				ID3D11ShaderResourceView* heightmapTextView;
				ID3D11ShaderResourceView* normalTextView;
				ID3D11ShaderResourceView* shininessTextView;
				ID3D11ShaderResourceView* opacityTextView;
				ID3D11ShaderResourceView* displacementTextView;
				ID3D11ShaderResourceView* lightmapTextView;
				ID3D11ShaderResourceView* reflectionTextView;
			};

			__declspec(align(16))
			struct TransformationBuff
			{
				DirectX::XMFLOAT4X4 world;
				DirectX::XMFLOAT4X4 worldInverseTranspose;
				DirectX::XMFLOAT4X4 WVP;
			};

			__declspec(align(16))
			struct EyeBuff
			{
				DirectX::XMFLOAT3 eye;
			};

			struct Transformation
			{
				DirectX::XMFLOAT4X4 world;
				DirectX::XMFLOAT4X4 worldInverseTranspose;
			};

			struct Renderable
			{
				void release()
				{
					mesh.release();
					material.release();
				}

				Transformation transformation;
				Mesh mesh;
				Material material;
			};

			struct DirectionalLight
			{
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;
				DirectX::XMFLOAT3 direction;
				float pad;
			};

			struct PointLight
			{
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;
				DirectX::XMFLOAT3 position;
				float range;
				DirectX::XMFLOAT3 att;
				float pad;
			};

			struct SpotLight
			{
				DirectX::XMFLOAT4 ambient;
				DirectX::XMFLOAT4 diffuse;
				DirectX::XMFLOAT4 specular;
				DirectX::XMFLOAT3 position;
				float range;
				DirectX::XMFLOAT3 direction;
				float spot;
				DirectX::XMFLOAT3 att;
				float pad; 
			};


			const uint_fast32_t MAX_NUM_LIGHTS = 32;
			__declspec(align(16))
			struct LightBuff
			{
				LightBuff() :
					numDirLights(0),
					numPointLights(0),
					numSpotLights(0)
				{
				}
				DirectionalLight directionalLights[MAX_NUM_LIGHTS];
				PointLight pointLights[MAX_NUM_LIGHTS];
				SpotLight spotLights[MAX_NUM_LIGHTS];
				unsigned int numDirLights;
				unsigned int numPointLights;
				unsigned int numSpotLights;
			};
		}
	}
}

#endif