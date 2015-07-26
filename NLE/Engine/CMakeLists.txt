PROJECT(NLE)

SET(HEADERS 
	NL_D3D11Device.h
	NL_D3D11Device.inl
	NL_DllApi.h
	NL_CameraController.h
	NL_ICameraController.h
	NL_InputProcessor.h
	NL_IInputProcessor.h	
	NL_INle.h
	NL_InputEvents.h
	NL_Nle.h
	NL_Renderer.h
	NL_RenderingEngine.h
	NL_IRenderer.h
	NL_RenderingResources.h
	NL_SharedContainers.h
	NL_Systems.h
	#NL_TextureLoader.h
	
	#DDSTextureLoader.h
	#WICTextureLoader.h
	)

SET (SHADERS
	Shaders/Forward_Pos_VS.hlsl
	Shaders/Forward_Pos_PS.hlsl
	Shaders/Forward_PosText_VS.hlsl
	Shaders/Forward_PosText_PS.hlsl
	Shaders/Forward_PosNormText_VS.hlsl
	Shaders/Forward_PosNormText_PS.hlsl
	Shaders/DeferredGBuff_TextNormal_BlinnPhong_VS.hlsl
	Shaders/DeferredGBuff_TextNormal_BlinnPhong_PS.hlsl
	)

SET(SOURCES 
	NL_CameraController.cpp
	NL_D3D11Device.cpp
	NL_InputProcessor.cpp
	NL_Nle.cpp
	NL_Renderer.cpp
	NL_RenderingEngine.cpp
	#NL_TextureLoader.cpp
	
	#DDSTextureLoader.cpp
	#WICTextureLoader.cpp
	)

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
	)

IF(NLE_HOST_OS STREQUAL "Windows")
	ADD_DEFINITIONS(
	-DNLE_DLL
	-DNLE_DLL_EXPORT
	)
ENDIF(NLE_HOST_OS STREQUAL "Windows")

LINK_DIRECTORIES(
	${NLE_TBB_LIBRARY_DEBUG_PATH}
	${NLE_TBB_LIBRARY_RELEASE_PATH}
	${NLE_SDK_INSTALL_PATH}/lib
	${NLE_DIRECT_X_SDK_LIBRARY_DEBUG_PATH}
	${NLE_DIRECT_X_SDK_LIBRARY_RELEASE_PATH}
	)

add_library (NLE SHARED
  ${HEADERS}
  ${SOURCES}
  ${SHADERS}
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
	
	debug d3d11.lib
	optimized d3d11.lib
	debug d3dcompiler.lib
	optimized d3dcompiler.lib
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