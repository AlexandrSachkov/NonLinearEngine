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
	NL_AssetImporter.h
	NL_Atomic.h
	NL_CommonTypes.h
	NL_Console.h
	NL_DataCompressionManager.h
	NL_FileIOManager.h
	NL_Game.h
	NL_GlfwInputMap.h
	NL_GScene.h
	NL_InputProcessor.h
	NL_IInputProcessor.h	
	NL_InputEvents.h
	NL_MemoryManager.h
	NL_MemoryPool.h
	NL_Nle.h
	NL_Octree.h
	NL_RenderingEngine.h
	NL_IRenderingEngine.h
	NL_Scene.h
	NL_GameManager.h
	NL_IGameManager.h
	NL_ResourceManager.h
	NL_ScriptCallbacks.h
	NL_ScriptExecutor.h
	NL_Systems.h
	NL_TextureLoader.h
	NL_Timer.h	
	NL_ThreadLocal.h
	NL_UiManager.h
	NL_IUiManager.h
	
	NL_WindowManager.h
		
	NL_DeviceCore.h	
	NL_ExecutionDesc.h
	NL_ISystem.h
	NL_PContainer.h
	NL_PContainer.inl
	NL_ResourceManager.cpp
	NL_Scheduler.h
	NL_SysInitializer.h
	NL_SysTask.h
	NL_System.h
	NL_Task.h
	NL_Thread.h
	)

SET(SOURCES 
	NL_AssetImporter.cpp
	NL_Console.cpp
	NL_DataCompressionManager.cpp
	NL_FileIOManager.cpp
	NL_Game.cpp
	NL_GlfwInputMap.cpp
	NL_GScene.cpp
	NL_InputProcessor.cpp
	NL_MemoryManager.cpp
	NL_Nle.cpp
	NL_Octree.cpp
	NL_RenderingEngine.cpp
	NL_Scene.cpp
	NL_GameManager.cpp
	NL_ScriptCallbacks.cpp
	NL_ScriptExecutor.cpp
	NL_TextureLoader.cpp
	NL_Timer.cpp
	NL_UiManager.cpp
	NL_WindowManager.cpp
	
	NL_DeviceCore.cpp
	NL_Scheduler.cpp		
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


# KTX
SET(NLE_KTX_INCLUDE_PATH
	"" CACHE PATH "NLE KTX include path")

IF(NLE_KTX_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE KTX include path must be specified")
ENDIF(NLE_KTX_INCLUDE_PATH STREQUAL "")

SET(NLE_KTX_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE KTX library debug path")

IF(NLE_KTX_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE KTX library debug path must be specified")
ENDIF(NLE_KTX_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_KTX_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE KTX library release path")

IF(NLE_KTX_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE KTX library release path must be specified")
ENDIF(NLE_KTX_LIBRARY_RELEASE_PATH STREQUAL "")


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


# Rapid JSON
SET(NLE_RAPID_JSON_INCLUDE_PATH
	"" CACHE PATH "NLE Rapid JSON include path")

IF(NLE_RAPID_JSON_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Rapid JSON include path must be specified")
ENDIF(NLE_RAPID_JSON_INCLUDE_PATH STREQUAL "")


# LZ4
SET(NLE_LZ4_INCLUDE_PATH
	"" CACHE PATH "NLE LZ4 include path")

IF(NLE_LZ4_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE LZ4 include path must be specified")
ENDIF(NLE_LZ4_INCLUDE_PATH STREQUAL "")

SET(NLE_LZ4_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE LZ4 library debug path")

IF(NLE_LZ4_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE LZ4 library debug path must be specified")
ENDIF(NLE_LZ4_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_LZ4_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE LZ4 library release path")

IF(NLE_LZ4_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE LZ4 library release path must be specified")
ENDIF(NLE_LZ4_LIBRARY_RELEASE_PATH STREQUAL "")



INCLUDE_DIRECTORIES(
	${NLE_TBB_INCLUDE_PATH}
	${NLE_LUA_INCLUDE_PATH}
	${NLE_GLFW_INCLUDE_PATH}
	${NLE_GLEW_INCLUDE_PATH}
	${NLE_GLM_INCLUDE_PATH}
	${NLE_KTX_INCLUDE_PATH}
	${NLE_ASSIMP_INCLUDE_PATH}
	${NLE_RAPID_JSON_INCLUDE_PATH}
	${NLE_LZ4_INCLUDE_PATH}
	)

IF(NLE_HOST_OS STREQUAL "Windows")
	ADD_DEFINITIONS(
	-D_CRT_SECURE_NO_WARNINGS
	-D_SCL_SECURE_NO_WARNINGS
	-DKTX_OPENGL
	-DGLEW_STATIC 
	-D_WIN32_WINNT=0x0601
	-DWINVER=0x0601
	)
ENDIF(NLE_HOST_OS STREQUAL "Windows")

LINK_DIRECTORIES(
	${NLE_TBB_LIBRARY_DEBUG_PATH}
	${NLE_TBB_LIBRARY_RELEASE_PATH}
	${NLE_LUA_LIBRARY_DEBUG_PATH}
	${NLE_LUA_LIBRARY_RELEASE_PATH}
	${NLE_GLFW_LIBRARY_DEBUG_PATH}
	${NLE_GLFW_LIBRARY_RELEASE_PATH}
	${NLE_GLEW_LIBRARY_DEBUG_PATH}
	${NLE_GLEW_LIBRARY_RELEASE_PATH}
	${NLE_KTX_LIBRARY_DEBUG_PATH}
	${NLE_KTX_LIBRARY_RELEASE_PATH}
	${NLE_ASSIMP_LIBRARY_DEBUG_PATH}
	${NLE_ASSIMP_LIBRARY_RELEASE_PATH}
	${NLE_LZ4_LIBRARY_DEBUG_PATH}
	${NLE_LZ4_LIBRARY_RELEASE_PATH}
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
	
	debug lua51
	optimized lua51
	
	debug glfw3
	optimized glfw3
	
	debug glew32s
	optimized glew32s
	
	debug glu32
	optimized glu32
	
	debug opengl32
	optimized opengl32
	
	debug libktx
	optimized libktx

	debug assimpd
	optimized assimp

	debug lz4
	optimized lz4
	)

set_target_properties(NLE PROPERTIES DEBUG_POSTFIX _d)