#ifndef NL_RENDERING_ENGINE_H_
#define NL_RENDERING_ENGINE_H_

#include "NL_IRenderingEngine.h"
#include "NLCore\NL_System.h"
#include "NLCore\NL_SContainer.h"
#include "NL_RenderingResources.h"
#include "NL_Timer.h"
#include "NLCore\NL_Thread.h"

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#include "tbb/atomic.h"

#include <memory>
#include <cstdint>
#include <chrono>
#include <string>
#include <vector>

struct lua_State;
namespace NLE
{
	class Window;
	namespace Core
	{
		class IEngine;
		class ISystem;
		struct SysInitializer;
	}
	namespace IMPORTER
	{
		class AssetImporter;
	}
	namespace WINDOW
	{
		class IWindowManager;
	}
	namespace GRAPHICS
	{
		class Scene;

		class RenderingEngine : public Core::System, public IRenderingEngine
		{
		public:
			RenderingEngine();
			~RenderingEngine();

			bool initialize(Core::IEngine& engine, std::unique_ptr<Core::SysInitializer> const& initializer);
			void release();
			bool initialized();
			std::function<void()> const& getExecutionProcedure();
			Core::ISystem& getInterface();

			ID3D11Device* getDevice();

		private:
			void render();		

			bool _initialized;
			std::function<void()> _procedure;

			NLE::Core::Data::SContainer<DirectX::XMFLOAT4X4>* _viewProjection;
			NLE::Core::Data::SContainer<DirectX::XMFLOAT4>* _eye;
			NLE::Core::Data::SContainer<double>* _fps;
			NLE::Core::Data::SContainer<DirectX::XMFLOAT4>* _canvasBgColor;

			WINDOW::IWindowManager* _windowManager;
			Timer _timer;
			tbb::atomic<bool> _firstRun;
		};
	}
}

#endif