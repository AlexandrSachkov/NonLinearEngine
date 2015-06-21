PROJECT(NLApplication)

SET(HEADERS 
	NL_Application.h
	NL_IApplication.h
	)

SET(SOURCES 
	NL_Application.cpp
	NL_IApplication.cpp
	)

INCLUDE_DIRECTORIES(
	${NLE_TBB_INCLUDE_PATH}
	${NLE_SDK_INSTALL_PATH}/include/NLE/NLCore
	)
LINK_DIRECTORIES(
	${NLE_TBB_LIBRARY_DEBUG_PATH}
	${NLE_SDK_INSTALL_PATH}/lib
	)

IF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL NLE_TBB_LIBRARY_RELEASE_PATH)
ELSE(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL NLE_TBB_LIBRARY_RELEASE_PATH)
	LINK_DIRECTORIES(${NLE_TBB_LIBRARY_RELEASE_PATH})
ENDIF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL NLE_TBB_LIBRARY_RELEASE_PATH)



# Add library from source
ADD_LIBRARY (NLApplication
  ${HEADERS}
  ${SOURCES}
)

# Link external libraries
TARGET_LINK_LIBRARIES(NLApplication
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
	)

set_target_properties(NLApplication PROPERTIES DEBUG_POSTFIX _d)

install (TARGETS NLApplication 
	RUNTIME DESTINATION ${NLE_SDK_INSTALL_PATH}/bin
	LIBRARY DESTINATION ${NLE_SDK_INSTALL_PATH}/lib/shared
	ARCHIVE DESTINATION ${NLE_SDK_INSTALL_PATH}/lib
	)

install (FILES ${HEADERS} DESTINATION ${NLE_SDK_INSTALL_PATH}/include/NLE/${PROJECT_NAME})