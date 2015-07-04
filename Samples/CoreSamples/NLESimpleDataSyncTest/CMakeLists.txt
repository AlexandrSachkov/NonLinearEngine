PROJECT(NLESimpleDataSyncTest)

SET(HEADERS 
	ReaderSystem.h
	SharedDataId.h
	WriterSystem.h
	)
SET(SOURCES
	DataSyncTest.cpp 
	ReaderSystem.cpp
	WriterSystem.cpp
	)

INCLUDE_DIRECTORIES(
	${NLE_SDK_INCLUDE_PATH}
	${NLE_TBB_INCLUDE_PATH}
	)

LINK_DIRECTORIES(
	${NLE_SDK_LIBRARY_DEBUG_PATH}
	${NLE_SDK_LIBRARY_RELEASE_PATH}
	${NLE_TBB_LIBRARY_DEBUG_PATH}
	${NLE_TBB_LIBRARY_RELEASE_PATH}
	)

ADD_EXECUTABLE (NLESimpleDataSyncTest
  ${HEADERS}
  ${SOURCES}
)

TARGET_LINK_LIBRARIES(NLESimpleDataSyncTest
	debug NLCore_d
	optimized NLCore
	
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

set_target_properties(NLESimpleDataSyncTest PROPERTIES DEBUG_POSTFIX _d)
install (TARGETS NLESimpleDataSyncTest 
	RUNTIME DESTINATION ${NLE_SAMPLE_INSTALL_PATH}/CoreSamples/${PROJECT_NAME}
	)
