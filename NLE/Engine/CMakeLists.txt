PROJECT(NLE)

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
	)

#SET (SHADERS 

#	)

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
	
	debug glew32s
	optimized glew32s
	
	debug glu32
	optimized glu32
	
	debug opengl32
	optimized opengl32
	)

set_target_properties(NLE PROPERTIES DEBUG_POSTFIX _d)
install (
	TARGETS NLE
	RUNTIME DESTINATION ${NLE_SDK_INSTALL_PATH}/bin
	LIBRARY DESTINATION ${NLE_SDK_INSTALL_PATH}/lib/shared
	ARCHIVE DESTINATION ${NLE_SDK_INSTALL_PATH}/lib
	)

install (FILES ${HEADERS} DESTINATION ${NLE_SDK_INSTALL_PATH}/include/${PROJECT_NAME})

IF(MSVC)
  INSTALL ( DIRECTORY ${PROJECT_BINARY_DIR}/Debug/
    DESTINATION ${NLE_SDK_INSTALL_PATH}/bin
	CONFIGURATIONS Debug
	FILES_MATCHING
    PATTERN *.pdb
    )
ENDIF(MSVC)

INSTALL ( DIRECTORY ${PROJECT_SOURCE_DIR}/Shaders/
    DESTINATION ${NLE_SDK_INSTALL_PATH}/bin
	FILES_MATCHING
    PATTERN *.hlsl
    )