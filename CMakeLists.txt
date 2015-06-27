CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT (NonLinearEngine)

set (NLE_VERSION_MAJOR 0)
set (NLE_VERSION_MINOR 9)
set (NLE_VERSION_PATCH 0)


IF(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /WX /arch:AVX /Ox /Ob2 /Ot /Gt")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /WX /arch:AVX /Od /Ob0")
ENDIF(MSVC)

# Configuration GUI goes here

# NLE install path config
SET(NLE_SDK_INSTALL_PATH 
	${PROJECT_BINARY_DIR}/${PROJECT_NAME} CACHE PATH "NLE SDK Installation Directory")
IF(NLE_SDK_INSTALL_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE SDK Installation Directory must be specified")
ENDIF(NLE_SDK_INSTALL_PATH STREQUAL "")

#Sample build toggle
SET(NLE_BUILD_CORE_SAMPLES
	ON CACHE BOOL "Build NLE Core Samples")

SET(NLE_BUILD_ENGINE_SAMPLES
	ON CACHE BOOL "Build NLE Engine Samples")


SET(NLE_SAMPLES_INSTALL_PATH 
	${NLE_SDK_INSTALL_PATH}/Samples CACHE PATH "NLE Samples Installation Directory")
IF(NLE_BUILD_CORE_SAMPLES AND NLE_BUILD_ENGINE_SAMPLES AND NLE_SAMPLES_INSTALL_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "NLE Samples Installation Directory must be specified")
ENDIF(NLE_BUILD_CORE_SAMPLES AND NLE_BUILD_ENGINE_SAMPLES AND NLE_SAMPLES_INSTALL_PATH STREQUAL "")

# NLE build config
SET(NLE_HOST_OS CACHE STRING "Host Operating System. Choose: \n\n Windows")
IF(NLE_HOST_OS STREQUAL "")
	MESSAGE(SEND_ERROR "Host Operating System must be specified")
ENDIF(NLE_HOST_OS STREQUAL "")

SET(NLE_TARGET_ARCHITECTURE CACHE STRING "Target Architecture. Choose: \n\n x86 \n x64")
IF(NLE_TARGET_ARCHITECTURE STREQUAL "")
	MESSAGE(SEND_ERROR "Target Architecture must be specified")
ENDIF(NLE_TARGET_ARCHITECTURE STREQUAL "")

# =====================================================================================

#                                     Global includes

# =====================================================================================

# TBB

SET(NLE_TBB_INCLUDE_PATH
	"" CACHE PATH "TBB include path")

IF(NLE_TBB_INCLUDE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "TBB include path must be specified")
ENDIF(NLE_TBB_INCLUDE_PATH STREQUAL "")

SET(NLE_TBB_LIBRARY_DEBUG_PATH
	"" CACHE PATH "TBB library debug path")

IF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "TBB library debug path must be specified")
ENDIF(NLE_TBB_LIBRARY_DEBUG_PATH STREQUAL "")

SET(NLE_TBB_LIBRARY_RELEASE_PATH
	"" CACHE PATH "TBB library release path")

IF(NLE_TBB_LIBRARY_RELEASE_PATH STREQUAL "")
	MESSAGE(SEND_ERROR "TBB library release path must be specified")
ENDIF(NLE_TBB_LIBRARY_RELEASE_PATH STREQUAL "")


# =====================================================================================

#                                     Optional system toggle

# =====================================================================================

# NLE
SET(NLE_BUILD_ENGINE
	ON CACHE BOOL "Build NonLinear Engine")


# =====================================================================================

SET(NLE_ROOT_DIR ${PROJECT_SOURCE_DIR})

ADD_SUBDIRECTORY(NLE)
ADD_SUBDIRECTORY(Samples)
