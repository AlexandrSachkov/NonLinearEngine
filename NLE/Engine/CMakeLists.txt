PROJECT(NLE)

SET(HEADERS 
	NL_Application.h
	NL_IApplication.h
	NL_InputEvents.h
	NL_DllApi.h
	NL_Nle.h
	NL_INle.h
	)

SET(SOURCES 
	NL_Application.cpp
	NL_IApplication.cpp
	NL_Nle.cpp
	)


INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}
	${NLE_SDK_INSTALL_PATH}/include/NLE
	${NLE_TBB_INCLUDE_PATH}
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
	)

set_target_properties(NLE PROPERTIES DEBUG_POSTFIX _d)
install (
	TARGETS NLE 
	RUNTIME DESTINATION ${NLE_SDK_INSTALL_PATH}/bin
	LIBRARY DESTINATION ${NLE_SDK_INSTALL_PATH}/lib/shared
	ARCHIVE DESTINATION ${NLE_SDK_INSTALL_PATH}/lib
	)

install (FILES ${HEADERS} DESTINATION ${NLE_SDK_INSTALL_PATH}/include/${PROJECT_NAME})