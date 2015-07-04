PROJECT(NLELargeDataSyncTest)

SET(HEADERS 
	TestSystem.h
	Data.h
	)
SET(SOURCES
	DataSyncTest.cpp 
	TestSystem.cpp
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

ADD_EXECUTABLE (NLELargeDataSyncTest
  ${HEADERS}
  ${SOURCES}
)

TARGET_LINK_LIBRARIES(NLELargeDataSyncTest 
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

set_target_properties(NLELargeDataSyncTest PROPERTIES DEBUG_POSTFIX _d)
install (TARGETS NLELargeDataSyncTest 
	RUNTIME DESTINATION ${NLE_SAMPLE_INSTALL_PATH}/CoreSamples/${PROJECT_NAME}
	)
