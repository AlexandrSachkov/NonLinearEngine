PROJECT(NLE)

SET(HEADERS 
	NL_Application.h
	NL_IApplication.h
	NL_DllApi.h
	NL_Nle.h
	NL_INle.h
	)

SET(SOURCES 
	NL_Application.cpp
	NL_IApplication.cpp
	NL_Nle.cpp)


SET(NLE_SFML_INCLUDE_PATH
	"" CACHE PATH "NLE SDL2 include path")

IF(NLE_SFML_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE SDL2 include path must be specified")
ENDIF(NLE_SFML_INCLUDE_PATH STREQUAL "")

SET(NLE_SFML_LIBRARY_DEBUG_PATH
	"" CACHE PATH "NLE SDL2 library debug path")

IF(NLE_SFML_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE SDL2 library debug path must be specified")
ENDIF(NLE_SFML_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_SFML_LIBRARY_RELEASE_PATH
	"" CACHE PATH "NLE SDL2 library release path")

IF(NLE_SFML_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE SDL2 library release path must be specified")
ENDIF(NLE_SFML_LIBRARY_RELEASE_PATH STREQUAL "")


INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}
	${NLE_SDK_INSTALL_PATH}/include/NLE
	${NLE_TBB_INCLUDE_PATH}
	${NLE_SFML_INCLUDE_PATH}
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
	${NLE_SFML_LIBRARY_DEBUG_PATH}
	${NLE_SFML_LIBRARY_RELEASE_PATH}
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
	
	debug sfml-system-d
	optimized sfml-system
	debug sfml-window-d
	optimized sfml-window-d
	
	debug NLCore_d
	optimized NLCore
	)

set_target_properties(NLE PROPERTIES DEBUG_POSTFIX _d)
install (
	TARGETS NLE 
	RUNTIME DESTINATION ${NLE_SDK_INSTALL_PATH}/bin
	LIBRARY DESTINATION ${NLE_SDK_INSTALL_PATH}/lib/shared
	ARCHIVE DESTINATION ${NLE_SDK_INSTALL_PATH}/lib
	)

install (FILES ${HEADERS} DESTINATION ${NLE_SDK_INSTALL_PATH}/include/${PROJECT_NAME})