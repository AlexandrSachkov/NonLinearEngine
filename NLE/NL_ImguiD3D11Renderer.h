#pragma once

struct ImDrawData;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;
struct ID3D10Blob;
struct ID3D11VertexShader;
struct ID3D11InputLayout;
struct ID3D11PixelShader;
struct ID3D11SamplerState;
struct ID3D11ShaderResourceView;
struct ID3D11RasterizerState;
struct ID3D11BlendState;
struct ID3D11DepthStencilState;

namespace NLE
{
	namespace GRAPHICS
	{
		class ImguiD3D11Renderer
		{
		public:
			ImguiD3D11Renderer();
			~ImguiD3D11Renderer();

			bool initialize(ID3D11Device* device, ID3D11DeviceContext* devCon);
			void render(ID3D11Device* device, ID3D11DeviceContext* devCon, ImDrawData* data);

		private:
			bool createDeviceObjects(ID3D11Device* device, ID3D11DeviceContext* devCon);
			bool createFontAndTextures(ID3D11Device* device, ID3D11DeviceContext* devCon);

			ID3D11Buffer*            _vertexBuffer;
			ID3D11Buffer*            _indexBuffer;
			ID3D10Blob*             _vertexShaderBlob;
			ID3D11VertexShader*      _vertexShader;
			ID3D11InputLayout*       _inputLayout;
			ID3D11Buffer*            _vertexConstantBuffer;
			ID3D10Blob *             _pixelShaderBlob;
			ID3D11PixelShader*       _pixelShader;
			ID3D11SamplerState*      _fontSampler;
			ID3D11ShaderResourceView*_fontTextureView;
			ID3D11RasterizerState*   _rasterizerState;
			ID3D11BlendState*        _blendState;
			ID3D11DepthStencilState* _depthStencilState;
			int                      _vertexBufferSize;
			int						_indexBufferSize;
		};
	}
}