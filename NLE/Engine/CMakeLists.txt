PROJECT(NLE)

SET(HEADERS 
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
	NL_SharedContainers.h
	NL_Systems.h
	)

SET(SOURCES 
	NL_CameraController.cpp
	NL_InputProcessor.cpp
	NL_Nle.cpp
	NL_Renderer.cpp
	NL_RenderingEngine.cpp
	)

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
	${NLE_GLEW_INCLUDE_PATH}
	${NLE_GLM_INCLUDE_PATH}
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
	${NLE_GLEW_LIBRARY_DEBUG_PATH}
	${NLE_GLEW_LIBRARY_RELEASE_PATH}
	)

add_library (NLE SHARED
  ${HEADERS}
  ${SOURCES}
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
	
	debug glew32
	optimized glew32
	
	debug opengl32.lib
	optimized opengl32.lib
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