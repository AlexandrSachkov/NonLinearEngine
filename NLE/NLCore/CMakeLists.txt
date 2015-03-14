PROJECT(NLCore)

SET(HEADERS 
	NL_Core.h
	NL_MemManager.h
	NL_MemPool.h
	NL_Scheduler.h
	NL_SObject.h
	NL_SScene.h
	NL_System.h
	NL_UObject.h
	NL_UScene.h
	)
SET(SOURCES 
	NL_Core.cpp
	NL_MemManager.cpp
	NL_MemPool.cpp
	NL_Scheduler.cpp
	NL_SObject.cpp
	NL_SScene.cpp
	NL_System.cpp
	NL_UObject.cpp
	NL_UScene.cpp
	)

INCLUDE_DIRECTORIES(${NLE_TBB_INCLUDE_PATH})
LINK_DIRECTORIES(${NLE_TBB_LIBRARY_DEBUG_PATH})

IF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL NLE_TBB_LIBRARY_RELEASE_PATH)
ELSE(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL NLE_TBB_LIBRARY_RELEASE_PATH)
	LINK_DIRECTORIES(${NLE_TBB_LIBRARY_RELEASE_PATH})
ENDIF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL NLE_TBB_LIBRARY_RELEASE_PATH)



# Add library from source
ADD_LIBRARY (NLCore
  ${HEADERS}
  ${SOURCES}
)

# Link external libraries
TARGET_LINK_LIBRARIES(NLCore
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

set_target_properties(NLCore PROPERTIES DEBUG_POSTFIX _d)

install (TARGETS NLCore 
	RUNTIME DESTINATION ${NLE_SDK_INSTALL_PATH}/bin
	LIBRARY DESTINATION ${NLE_SDK_INSTALL_PATH}/lib/shared
	ARCHIVE DESTINATION ${NLE_SDK_INSTALL_PATH}/lib
	)

install (FILES ${HEADERS} DESTINATION ${NLE_SDK_INSTALL_PATH}/include/NLE/${PROJECT_NAME})