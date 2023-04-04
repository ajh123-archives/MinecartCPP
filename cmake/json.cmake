set(JSON_VERSION "v3.11.2")
find_package(json QUIET) # QUIET or REQUIRED
if (NOT json_FOUND) # If there's none, fetch and build json
	include(FetchContent)
	FetchContent_Declare(
		json
		URL https://github.com/nlohmann/json/archive/refs/tags/${JSON_VERSION}.tar.gz
	)
	FetchContent_GetProperties(json)
	if (NOT json_POPULATED) # Have we downloaded json yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(json)
		add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
		set(JSON_INCLUDE_DIR ${json_SOURCE_DIR}/include)
	endif()
endif()
