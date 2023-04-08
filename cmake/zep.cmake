set(ZEP_VERSION "v0.1.12")
find_package(zep QUIET) # QUIET or REQUIRED
if (NOT zep_FOUND) # If there's none, fetch and build zep
	include(FetchContent)
	FetchContent_Declare(
		zep
		URL https://github.com/Rezonality/zep/archive/refs/tags/${ZEP_VERSION}.tar.gz
	)
	FetchContent_GetProperties(zep)
	if (NOT zep_POPULATED) # Have we downloaded zep yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(zep)
		set(BUILD_IMGUI OFF CACHE BOOL "" FORCE)
		set(BUILD_DEMOS OFF CACHE BOOL "" FORCE)
		set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
		set(ZEP_FEATURE_CPP_FILE_SYSTEM OFF CACHE BOOL "" FORCE)
		set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
		add_subdirectory(${zep_SOURCE_DIR} ${zep_BINARY_DIR})
		set(ZEP_INCLUDE_DIR ${zep_SOURCE_DIR}/include)
	endif()
endif()
