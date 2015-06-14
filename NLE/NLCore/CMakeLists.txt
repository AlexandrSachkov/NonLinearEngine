PROJECT(NLCore)

SET(HEADERS 
	NL_Clock.h
	NL_DataRequest.h
	NL_DeviceCore.h
	NL_Distributor.h
	NL_ExecutionDesc.h
	NL_MasterContainer.h
	NL_MasterContainer.inl
	NL_MSDistributor.h
	NL_MSDistributor.inl
	NL_PContainer.h
	NL_PContainer.inl
	NL_SContainer.h
	NL_SContainer.inl
	NL_SDistributor.h
	NL_SDistributor.inl
	NL_SlaveContainer.h
	NL_SlaveContainer.inl
	NL_Scheduler.h
	NL_StateManager.h
	NL_SysManager.h
	NL_SysTask.h
	NL_System.h
	)
SET(SOURCES 
	NL_Clock.cpp
	NL_DeviceCore.cpp
	NL_Scheduler.cpp		
	NL_SysManager.cpp
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