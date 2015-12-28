CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT (NonLinearEngine)

set (NLE_VERSION_MAJOR 0)
set (NLE_VERSION_MINOR 9)
set (NLE_VERSION_PATCH 0)


IF(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD /WX /arch:AVX /Ox /Ob2 /Ot /Gt /Zc:implicitNoexcept-")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd /WX /arch:AVX /Od /Ob0 /Zc:implicitNoexcept-")
ENDIF(MSVC)

# Configuration GUI goes here

# NLE build config
SET(NLE_HOST_OS CACHE STRING "Host Operating System. Choose: \n\n Windows")
IF(NLE_HOST_OS STREQUAL "")
	MESSAGE(SEND_ERROR "Host Operating System must be specified")
ENDIF(NLE_HOST_OS STREQUAL "")

SET(NLE_TARGET_ARCHITECTURE CACHE STRING "Target Architecture. Choose: \n\n x86 \n x64")
IF(NLE_TARGET_ARCHITECTURE STREQUAL "")
	MESSAGE(SEND_ERROR "Target Architecture must be specified")
ENDIF(NLE_TARGET_ARCHITECTURE STREQUAL "")

# =====================================================================================

#                                     Global includes

# =====================================================================================

SET(HEADERS 
	NL_Allocator.h
	NL_Atomic.h
	NL_AssetImporter.h
	NL_Camera.h
	NL_CameraManager.h
	NL_ICameraManager.h
	NL_Console.h
	NL_ConsoleOutType.h
	NL_D3D11Utility.h
	NL_D3D11Utility.inl
	NL_GlfwInputMap.h
	NL_GScene.h
	NL_InputProcessor.h
	NL_IInputProcessor.h	
	NL_InputEvents.h
	NL_Nle.h
	NL_RenderingEngine.h
	NL_IRenderingEngine.h
	NL_RenderingResources.h
	NL_SceneManager.h
	NL_ISceneManager.h
	NL_ScriptCallbacks.h
	NL_ScriptExecutor.h
	NL_SharedContainers.h
	NL_Systems.h
	NL_TextureLoader.h
	NL_Timer.h
	NL_ThreadLocal.h
	NL_UiManager.h
	NL_IUiManager.h
	NL_WindowManager.h
	NL_IWindowManager.h
	
	DDSTextureLoader.h
	WICTextureLoader.h
	
	NL_AsyncTask.h 
	NL_DeviceCore.h	
	NL_ExecutionDesc.h
	NL_IEngine.h
	NL_ISystem.h
	NL_PContainer.h
	NL_PContainer.inl
	NL_Scheduler.h
	NL_SyncTask.h
	NL_SysInitializer.h
	NL_SysManager.h	
	NL_SysThread.h
	NL_System.h
	NL_Thread.h
	)

SET(SOURCES 
	NL_AssetImporter.cpp
	NL_Camera.cpp
	NL_CameraManager.cpp
	NL_Console.cpp
	NL_D3D11Utility.cpp
	NL_GlfwInputMap.cpp
	NL_GScene.cpp
	NL_InputProcessor.cpp
	NL_Nle.cpp
	NL_RenderingEngine.cpp
	NL_SceneManager.cpp
	NL_ScriptCallbacks.cpp
	NL_ScriptExecutor.cpp
	NL_TextureLoader.cpp
	NL_Timer.cpp
	NL_UiManager.cpp
	NL_WindowManager.cpp
	
	DDSTextureLoader.cpp
	WICTextureLoader.cpp
	
	NL_DeviceCore.cpp
	NL_Scheduler.cpp		
	NL_SysManager.cpp
	NL_SysThread.cpp
	NL_Thread.cpp
	)


# TBB

SET(NLE_TBB_INCLUDE_PATH
	"" CACHE PATH "TBB include path")

IF(NLE_TBB_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "TBB include path must be specified")
ENDIF(NLE_TBB_INCLUDE_PATH STREQUAL "")

SET(NLE_TBB_LIBRARY_DEBUG_PATH
	"" CACHE PATH "TBB library debug path")

IF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "TBB library debug path must be specified")
ENDIF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_TBB_LIBRARY_RELEASE_PATH
	"" CACHE PATH "TBB library release path")

IF(NLE_TBB_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "TBB library release path must be specified")
ENDIF(NLE_TBB_LIBRARY_RELEASE_PATH STREQUAL "")


# DirectX SDK
SET(NLE_DIRECT_X_SDK_INCLUDE_PATH
	"" CACHE PATH "NLE DirectX SDK include path")

IF(NLE_DIRECT_X_SDK_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE DirectX SDK include path must be specified")
ENDIF(NLE_DIRECT_X_SDK_INCLUDE_PATH STREQUAL "")

SET(NLE_DIRECT_X_SDK_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE DirectX SDK library debug path")

IF(NLE_DIRECT_X_SDK_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE DirectX SDK library debug path must be specified")
ENDIF(NLE_DIRECT_X_SDK_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_DIRECT_X_SDK_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE DirectX SDK library release path")

IF(NLE_DIRECT_X_SDK_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE DirectX SDK library release path must be specified")
ENDIF(NLE_DIRECT_X_SDK_LIBRARY_RELEASE_PATH STREQUAL "")


# Assimp
SET(NLE_ASSIMP_INCLUDE_PATH
	"" CACHE PATH "NLE Assimp include path")

IF(NLE_ASSIMP_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Assimp include path must be specified")
ENDIF(NLE_ASSIMP_INCLUDE_PATH STREQUAL "")

SET(NLE_ASSIMP_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE Assimp library debug path")

IF(NLE_ASSIMP_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Assimp library debug path must be specified")
ENDIF(NLE_ASSIMP_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_ASSIMP_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE Assimp library release path")

IF(NLE_ASSIMP_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Assimp library release path must be specified")
ENDIF(NLE_ASSIMP_LIBRARY_RELEASE_PATH STREQUAL "")


# Lua
SET(NLE_LUA_INCLUDE_PATH
	"" CACHE PATH "NLE Lua include path")

IF(NLE_LUA_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Lua include path must be specified")
ENDIF(NLE_LUA_INCLUDE_PATH STREQUAL "")

SET(NLE_LUA_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE Lua library debug path")

IF(NLE_LUA_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Lua library debug path must be specified")
ENDIF(NLE_LUA_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_LUA_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE Lua library release path")

IF(NLE_LUA_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Lua library release path must be specified")
ENDIF(NLE_LUA_LIBRARY_RELEASE_PATH STREQUAL "")


# GLFW
SET(NLE_GLFW_INCLUDE_PATH
	"" CACHE PATH "NLE GLFW include path")

IF(NLE_GLFW_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE GLFW include path must be specified")
ENDIF(NLE_GLFW_INCLUDE_PATH STREQUAL "")

SET(NLE_GLFW_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE GLFW library debug path")

IF(NLE_GLFW_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE GLFW library debug path must be specified")
ENDIF(NLE_GLFW_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_GLFW_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE GLFW library release path")

IF(NLE_GLFW_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE GLFW library release path must be specified")
ENDIF(NLE_GLFW_LIBRARY_RELEASE_PATH STREQUAL "")


# GLEW
SET(NLE_GLEW_INCLUDE_PATH
	"" CACHE PATH "NLE GLEW include path")

IF(NLE_GLEW_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE GLEW include path must be specified")
ENDIF(NLE_GLEW_INCLUDE_PATH STREQUAL "")

SET(NLE_GLEW_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE GLEW library debug path")

IF(NLE_GLEW_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE GLEW library debug path must be specified")
ENDIF(NLE_GLEW_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_GLEW_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE GLEW library release path")

IF(NLE_GLEW_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE GLEW library release path must be specified")
ENDIF(NLE_GLEW_LIBRARY_RELEASE_PATH STREQUAL "")


# GLM
SET(NLE_GLM_INCLUDE_PATH
	"" CACHE PATH "NLE GLM include path")

IF(NLE_GLM_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE GLM include path must be specified")
ENDIF(NLE_GLM_INCLUDE_PATH STREQUAL "")


INCLUDE_DIRECTORIES(
	${NLE_SDK_INSTALL_PATH}/include/NLE
	${NLE_TBB_INCLUDE_PATH}
	${NLE_DIRECT_X_SDK_INCLUDE_PATH}
	${NLE_ASSIMP_INCLUDE_PATH}
	${NLE_LUA_INCLUDE_PATH}
	${NLE_GLFW_INCLUDE_PATH}
	${NLE_GLEW_INCLUDE_PATH}
	${NLE_GLM_INCLUDE_PATH}
	)

IF(NLE_HOST_OS STREQUAL "Windows")
	ADD_DEFINITIONS(
	-DGLEW_STATIC 
	-D_WIN32_WINNT=0x0601
	-DWINVER=0x0601
	)
ENDIF(NLE_HOST_OS STREQUAL "Windows")

LINK_DIRECTORIES(
	${NLE_TBB_LIBRARY_DEBUG_PATH}
	${NLE_TBB_LIBRARY_RELEASE_PATH}
	${NLE_SDK_INSTALL_PATH}/lib
	${NLE_DIRECT_X_SDK_LIBRARY_DEBUG_PATH}
	${NLE_DIRECT_X_SDK_LIBRARY_RELEASE_PATH}
	${NLE_ASSIMP_LIBRARY_DEBUG_PATH}
	${NLE_ASSIMP_LIBRARY_RELEASE_PATH}
	${NLE_LUA_LIBRARY_DEBUG_PATH}
	${NLE_LUA_LIBRARY_RELEASE_PATH}
	${NLE_GLFW_LIBRARY_DEBUG_PATH}
	${NLE_GLFW_LIBRARY_RELEASE_PATH}
	${NLE_GLEW_LIBRARY_DEBUG_PATH}
	${NLE_GLEW_LIBRARY_RELEASE_PATH}
	)

add_executable (NLE
  ${HEADERS}
  ${SOURCES}
  #${SHADERS}
)

TARGET_LINK_LIBRARIES(NLE 
	debug tbb_debug
	optimized tbb
	debug tbb_preview_debug
	optimized tbb_preview
	debug tbbmalloc_debug
	optimized tbbmalloc
	debug tbbmalloc_proxy_debug
	optimized tbbmalloc_proxy
	debug tbbproxy_debug
	optimized tbbproxy
	
	debug NLCore_d
	optimized NLCore
	
	debug d3d11
	optimized d3d11
	debug d3dcompiler
	optimized d3dcompiler
	
	debug assimpd
	optimized assimp
	
	debug lua51
	optimized lua51
	
	debug glfw3
	optimized glfw3
	
	debug glew32
	optimized glew32
	
	debug glu32
	optimized glu32
	
	debug opengl32
	optimized opengl32
	)

set_target_properties(NLE PROPERTIES DEBUG_POSTFIX _d)