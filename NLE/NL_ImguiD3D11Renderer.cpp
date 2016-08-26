#include "NL_ImguiD3D11Renderer.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <imgui.h>

namespace NLE
{
	namespace GRAPHICS
	{
		struct VERTEX_CONSTANT_BUFFER
		{
			float        mvp[4][4];
		};

		ImguiD3D11Renderer::ImguiD3D11Renderer() :
			_vertexBuffer(nullptr),
			_indexBuffer(nullptr),
			_vertexShaderBlob(nullptr),
			_vertexShader(nullptr),
			_inputLayout(nullptr),
			_vertexConstantBuffer(nullptr),
			_pixelShaderBlob(nullptr),
			_pixelShader(nullptr),
			_fontSampler(nullptr),
			_fontTextureView(nullptr),
			_rasterizerState(nullptr),
			_blendState(nullptr),
			_depthStencilState(nullptr),
			_vertexBufferSize(5000),
			_indexBufferSize(10000)
		{
		}

		ImguiD3D11Renderer::~ImguiD3D11Renderer()
		{

		}

		bool ImguiD3D11Renderer::initialize(ID3D11Device* device, ID3D11DeviceContext* devCon)
		{
			if (!createDeviceObjects(device, devCon))
				return false;

			if (!createFontAndTextures(device, devCon))
				return false;

			return true;
		}

		bool ImguiD3D11Renderer::createDeviceObjects(ID3D11Device* device, ID3D11DeviceContext* devCon)
		{
			// By using D3DCompile() from <d3dcompiler.h> / d3dcompiler.lib, we introduce a dependency to a given version of d3dcompiler_XX.dll (see D3DCOMPILER_DLL_A)
			// If you would like to use this DX11 sample code but remove this dependency you can: 
			//  1) compile once, save the compiled shader blobs into a file or source code and pass them to CreateVertexShader()/CreatePixelShader() [prefered solution]
			//  2) use code to detect any version of the DLL and grab a pointer to D3DCompile from the DLL. 
			// See https://github.com/ocornut/imgui/pull/638 for sources and details.

			// Create the vertex shader
			{
				static const char* vertexShader =
					"cbuffer vertexBuffer : register(b0) \
            {\
            float4x4 ProjectionMatrix; \
            };\
            struct VS_INPUT\
            {\
            float2 pos : POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            \
            struct PS_INPUT\
            {\
            float4 pos : SV_POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            \
            PS_INPUT main(VS_INPUT input)\
            {\
            PS_INPUT output;\
            output.pos = mul( ProjectionMatrix, float4(input.pos.xy, 0.f, 1.f));\
            output.col = input.col;\
            output.uv  = input.uv;\
            return output;\
            }";

				D3DCompile(vertexShader, strlen(vertexShader), nullptr, nullptr, nullptr, "main", "vs_4_0", 0, 0, &_vertexShaderBlob, nullptr);
				if (!_vertexShaderBlob) // NB: Pass ID3D10Blob* pErrorBlob to D3DCompile() to get error showing in (const char*)pErrorBlob->GetBufferPointer(). Make sure to Release() the blob!
					return false;

				if (device->CreateVertexShader((DWORD*)_vertexShaderBlob->GetBufferPointer(), _vertexShaderBlob->GetBufferSize(), nullptr, &_vertexShader) != S_OK)
					return false;

				// Create the input layout
				D3D11_INPUT_ELEMENT_DESC local_layout[] = {
					{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (size_t)(&((ImDrawVert*)0)->pos), D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, (size_t)(&((ImDrawVert*)0)->uv),  D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, (size_t)(&((ImDrawVert*)0)->col), D3D11_INPUT_PER_VERTEX_DATA, 0 },
				};

				if (device->CreateInputLayout(local_layout, 3, _vertexShaderBlob->GetBufferPointer(), _vertexShaderBlob->GetBufferSize(), &_inputLayout) != S_OK)
					return false;

				// Create the constant buffer
				{
					D3D11_BUFFER_DESC desc;
					desc.ByteWidth = sizeof(VERTEX_CONSTANT_BUFFER);
					desc.Usage = D3D11_USAGE_DYNAMIC;
					desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
					desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					desc.MiscFlags = 0;
					device->CreateBuffer(&desc, nullptr, &_vertexConstantBuffer);
				}
			}

			// Create the pixel shader
			{
				static const char* pixelShader =
					"struct PS_INPUT\
            {\
            float4 pos : SV_POSITION;\
            float4 col : COLOR0;\
            float2 uv  : TEXCOORD0;\
            };\
            sampler sampler0;\
            Texture2D texture0;\
            \
            float4 main(PS_INPUT input) : SV_Target\
            {\
            float4 out_col = input.col * texture0.Sample(sampler0, input.uv); \
            return out_col; \
            }";

				D3DCompile(pixelShader, strlen(pixelShader), nullptr, nullptr, nullptr, "main", "ps_4_0", 0, 0, &_pixelShaderBlob, nullptr);
				if (!_pixelShaderBlob)  // NB: Pass ID3D10Blob* pErrorBlob to D3DCompile() to get error showing in (const char*)pErrorBlob->GetBufferPointer(). Make sure to Release() the blob!
					return false;

				if (device->CreatePixelShader((DWORD*)_pixelShaderBlob->GetBufferPointer(), _pixelShaderBlob->GetBufferSize(), nullptr, &_pixelShader) != S_OK)
					return false;
			}

			// Create the blending setup
			{
				D3D11_BLEND_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				desc.AlphaToCoverageEnable = false;
				desc.RenderTarget[0].BlendEnable = true;
				desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
				desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
				desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
				desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
				desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
				desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
				device->CreateBlendState(&desc, &_blendState);
			}

			// Create the rasterizer state
			{
				D3D11_RASTERIZER_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				desc.FillMode = D3D11_FILL_SOLID;
				desc.CullMode = D3D11_CULL_NONE;
				desc.ScissorEnable = true;
				desc.DepthClipEnable = true;
				device->CreateRasterizerState(&desc, &_rasterizerState);
			}

			// Create depth-stencil State
			{
				D3D11_DEPTH_STENCIL_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				desc.DepthEnable = false;
				desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
				desc.StencilEnable = false;
				desc.FrontFace.StencilFailOp = desc.FrontFace.StencilDepthFailOp = desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				desc.BackFace = desc.FrontFace;
				device->CreateDepthStencilState(&desc, &_depthStencilState);
			}

			return true;
		}

		bool ImguiD3D11Renderer::createFontAndTextures(ID3D11Device* device, ID3D11DeviceContext* devCon)
		{
			// Build texture atlas
			ImGuiIO& io = ImGui::GetIO();
			unsigned char* pixels;
			int width, height;
			io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

			// Upload texture to graphics system
			{
				D3D11_TEXTURE2D_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				desc.Width = width;
				desc.Height = height;
				desc.MipLevels = 1;
				desc.ArraySize = 1;
				desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				desc.SampleDesc.Count = 1;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = 0;

				ID3D11Texture2D *pTexture = NULL;
				D3D11_SUBRESOURCE_DATA subResource;
				subResource.pSysMem = pixels;
				subResource.SysMemPitch = desc.Width * 4;
				subResource.SysMemSlicePitch = 0;
				device->CreateTexture2D(&desc, &subResource, &pTexture);

				// Create texture view
				D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
				ZeroMemory(&srvDesc, sizeof(srvDesc));
				srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Texture2D.MipLevels = desc.MipLevels;
				srvDesc.Texture2D.MostDetailedMip = 0;
				device->CreateShaderResourceView(pTexture, &srvDesc, &_fontTextureView);
				pTexture->Release();
			}

			// Store our identifier
			io.Fonts->TexID = (void *)_fontTextureView;

			// Create texture sampler
			{
				D3D11_SAMPLER_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				desc.MipLODBias = 0.f;
				desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
				desc.MinLOD = 0.f;
				desc.MaxLOD = 0.f;
				device->CreateSamplerState(&desc, &_fontSampler);
			}

			return true;
		}

		void ImguiD3D11Renderer::render(ID3D11Device* device, ID3D11DeviceContext* devCon, ImDrawData* drawData)
		{
			// Create and grow vertex/index buffers if needed
			if (!_vertexBuffer || _vertexBufferSize < drawData->TotalVtxCount)
			{
				if (_vertexBuffer) { _vertexBuffer->Release(); _vertexBuffer = nullptr; }
				_vertexBufferSize = drawData->TotalVtxCount + 5000;
				D3D11_BUFFER_DESC desc;
				memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.ByteWidth = _vertexBufferSize * sizeof(ImDrawVert);
				desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				desc.MiscFlags = 0;
				if (device->CreateBuffer(&desc, nullptr, &_vertexBuffer) < 0)
					return;
			}
			if (!_indexBuffer || _indexBufferSize < drawData->TotalIdxCount)
			{
				if (_indexBuffer) { _indexBuffer->Release(); _indexBuffer = nullptr; }
				_indexBufferSize = drawData->TotalIdxCount + 10000;
				D3D11_BUFFER_DESC desc;
				memset(&desc, 0, sizeof(D3D11_BUFFER_DESC));
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.ByteWidth = _indexBufferSize * sizeof(ImDrawIdx);
				desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				if (device->CreateBuffer(&desc, nullptr, &_indexBuffer) < 0)
					return;
			}

			// Copy and convert all vertices into a single contiguous buffer
			D3D11_MAPPED_SUBRESOURCE vtx_resource, idx_resource;
			if (devCon->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vtx_resource) != S_OK)
				return;
			if (devCon->Map(_indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &idx_resource) != S_OK)
				return;

			ImDrawVert* vtx_dst = (ImDrawVert*)vtx_resource.pData;
			ImDrawIdx* idx_dst = (ImDrawIdx*)idx_resource.pData;
			for (int n = 0; n < drawData->CmdListsCount; n++)
			{
				const ImDrawList* cmd_list = drawData->CmdLists[n];
				memcpy(vtx_dst, &cmd_list->VtxBuffer[0], cmd_list->VtxBuffer.size() * sizeof(ImDrawVert));
				memcpy(idx_dst, &cmd_list->IdxBuffer[0], cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
				vtx_dst += cmd_list->VtxBuffer.size();
				idx_dst += cmd_list->IdxBuffer.size();
			}
			devCon->Unmap(_vertexBuffer, 0);
			devCon->Unmap(_indexBuffer, 0);

			// Setup orthographic projection matrix into our constant buffer
			{
				D3D11_MAPPED_SUBRESOURCE mapped_resource;
				if (devCon->Map(_vertexConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource) != S_OK)
					return;

				VERTEX_CONSTANT_BUFFER* constant_buffer = (VERTEX_CONSTANT_BUFFER*)mapped_resource.pData;
				float L = 0.0f;
				float R = ImGui::GetIO().DisplaySize.x;
				float B = ImGui::GetIO().DisplaySize.y;
				float T = 0.0f;
				float mvp[4][4] =
				{
					{ 2.0f / (R - L),   0.0f,           0.0f,       0.0f },
					{ 0.0f,         2.0f / (T - B),     0.0f,       0.0f },
					{ 0.0f,         0.0f,           0.5f,       0.0f },
					{ (R + L) / (L - R),  (T + B) / (B - T),    0.5f,       1.0f },
				};
				memcpy(&constant_buffer->mvp, mvp, sizeof(mvp));
				devCon->Unmap(_vertexConstantBuffer, 0);
			}

			// Backup DX state that will be modified to restore it afterwards (unfortunately this is very ugly looking and verbose. Close your eyes!)
			struct BACKUP_DX11_STATE
			{
				UINT                        ScissorRectsCount, ViewportsCount;
				D3D11_RECT                  ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
				D3D11_VIEWPORT              Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
				ID3D11RasterizerState*      RS;
				ID3D11BlendState*           BlendState;
				FLOAT                       BlendFactor[4];
				UINT                        SampleMask;
				UINT                        StencilRef;
				ID3D11DepthStencilState*    DepthStencilState;
				ID3D11ShaderResourceView*   PSShaderResource;
				ID3D11SamplerState*         PSSampler;
				ID3D11PixelShader*          PS;
				ID3D11VertexShader*         VS;
				UINT                        PSInstancesCount, VSInstancesCount;
				ID3D11ClassInstance*        PSInstances[256], *VSInstances[256];   // 256 is max according to PSSetShader documentation
				D3D11_PRIMITIVE_TOPOLOGY    PrimitiveTopology;
				ID3D11Buffer*               IndexBuffer, *VertexBuffer, *VSConstantBuffer;
				UINT                        IndexBufferOffset, VertexBufferStride, VertexBufferOffset;
				DXGI_FORMAT                 IndexBufferFormat;
				ID3D11InputLayout*          InputLayout;
			};
			BACKUP_DX11_STATE old;
			old.ScissorRectsCount = old.ViewportsCount = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
			devCon->RSGetScissorRects(&old.ScissorRectsCount, old.ScissorRects);
			devCon->RSGetViewports(&old.ViewportsCount, old.Viewports);
			devCon->RSGetState(&old.RS);
			devCon->OMGetBlendState(&old.BlendState, old.BlendFactor, &old.SampleMask);
			devCon->OMGetDepthStencilState(&old.DepthStencilState, &old.StencilRef);
			devCon->PSGetShaderResources(0, 1, &old.PSShaderResource);
			devCon->PSGetSamplers(0, 1, &old.PSSampler);
			old.PSInstancesCount = old.VSInstancesCount = 256;
			devCon->PSGetShader(&old.PS, old.PSInstances, &old.PSInstancesCount);
			devCon->VSGetShader(&old.VS, old.VSInstances, &old.VSInstancesCount);
			devCon->VSGetConstantBuffers(0, 1, &old.VSConstantBuffer);
			devCon->IAGetPrimitiveTopology(&old.PrimitiveTopology);
			devCon->IAGetIndexBuffer(&old.IndexBuffer, &old.IndexBufferFormat, &old.IndexBufferOffset);
			devCon->IAGetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset);
			devCon->IAGetInputLayout(&old.InputLayout);

			// Setup viewport
			D3D11_VIEWPORT vp;
			memset(&vp, 0, sizeof(D3D11_VIEWPORT));
			vp.Width = ImGui::GetIO().DisplaySize.x;
			vp.Height = ImGui::GetIO().DisplaySize.y;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = vp.TopLeftY = 0.0f;
			devCon->RSSetViewports(1, &vp);

			// Bind shader and vertex buffers
			unsigned int stride = sizeof(ImDrawVert);
			unsigned int offset = 0;
			devCon->IASetInputLayout(_inputLayout);
			devCon->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
			devCon->IASetIndexBuffer(_indexBuffer, sizeof(ImDrawIdx) == 2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT, 0);
			devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			devCon->VSSetShader(_vertexShader, NULL, 0);
			devCon->VSSetConstantBuffers(0, 1, &_vertexConstantBuffer);
			devCon->PSSetShader(_pixelShader, NULL, 0);
			devCon->PSSetSamplers(0, 1, &_fontSampler);

			// Setup render state
			const float blend_factor[4] = { 0.f, 0.f, 0.f, 0.f };
			devCon->OMSetBlendState(_blendState, blend_factor, 0xffffffff);
			devCon->OMSetDepthStencilState(_depthStencilState, 0);
			devCon->RSSetState(_rasterizerState);

			// Render command lists
			int vtx_offset = 0;
			int idx_offset = 0;
			for (int n = 0; n < drawData->CmdListsCount; n++)
			{
				const ImDrawList* cmd_list = drawData->CmdLists[n];
				for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
				{
					const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
					if (pcmd->UserCallback)
					{
						pcmd->UserCallback(cmd_list, pcmd);
					}
					else
					{
						const D3D11_RECT r = { (LONG)pcmd->ClipRect.x, (LONG)pcmd->ClipRect.y, (LONG)pcmd->ClipRect.z, (LONG)pcmd->ClipRect.w };
						devCon->PSSetShaderResources(0, 1, (ID3D11ShaderResourceView**)&pcmd->TextureId);
						devCon->RSSetScissorRects(1, &r);
						devCon->DrawIndexed(pcmd->ElemCount, idx_offset, vtx_offset);
					}
					idx_offset += pcmd->ElemCount;
				}
				vtx_offset += cmd_list->VtxBuffer.size();
			}

			// Restore modified DX state
			devCon->RSSetScissorRects(old.ScissorRectsCount, old.ScissorRects);
			devCon->RSSetViewports(old.ViewportsCount, old.Viewports);
			devCon->RSSetState(old.RS); if (old.RS) old.RS->Release();
			devCon->OMSetBlendState(old.BlendState, old.BlendFactor, old.SampleMask); if (old.BlendState) old.BlendState->Release();
			devCon->OMSetDepthStencilState(old.DepthStencilState, old.StencilRef); if (old.DepthStencilState) old.DepthStencilState->Release();
			devCon->PSSetShaderResources(0, 1, &old.PSShaderResource); if (old.PSShaderResource) old.PSShaderResource->Release();
			devCon->PSSetSamplers(0, 1, &old.PSSampler); if (old.PSSampler) old.PSSampler->Release();
			devCon->PSSetShader(old.PS, old.PSInstances, old.PSInstancesCount); if (old.PS) old.PS->Release();
			for (UINT i = 0; i < old.PSInstancesCount; i++) if (old.PSInstances[i]) old.PSInstances[i]->Release();
			devCon->VSSetShader(old.VS, old.VSInstances, old.VSInstancesCount); if (old.VS) old.VS->Release();
			devCon->VSSetConstantBuffers(0, 1, &old.VSConstantBuffer); if (old.VSConstantBuffer) old.VSConstantBuffer->Release();
			for (UINT i = 0; i < old.VSInstancesCount; i++) if (old.VSInstances[i]) old.VSInstances[i]->Release();
			devCon->IASetPrimitiveTopology(old.PrimitiveTopology);
			devCon->IASetIndexBuffer(old.IndexBuffer, old.IndexBufferFormat, old.IndexBufferOffset); if (old.IndexBuffer) old.IndexBuffer->Release();
			devCon->IASetVertexBuffers(0, 1, &old.VertexBuffer, &old.VertexBufferStride, &old.VertexBufferOffset); if (old.VertexBuffer) old.VertexBuffer->Release();
			devCon->IASetInputLayout(old.InputLayout); if (old.InputLayout) old.InputLayout->Release();

		}
	}
}