set(LUA_BRANCH "master")
find_package(lua QUIET) # QUIET or REQUIRED
if (NOT lua_FOUND) # If there's none, fetch and build lua
	include(FetchContent)
	FetchContent_Declare(
		lua
		URL https://github.com/lua/lua/archive/${LUA_BRANCH}.tar.gz
	)
	FetchContent_GetProperties(lua)
	if (NOT lua_POPULATED) # Have we downloaded lua yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(lua)

		# Configure ImGui build
		set(LUA_INCLUDE_DIR ${lua_SOURCE_DIR})
		file(GLOB LUA_SOURCES ${LUA_INCLUDE_DIR}/*.c)
		file(GLOB LUA_HEADERS ${LUA_INCLUDE_DIR}/*.h)

		add_library(lua STATIC ${LUA_SOURCES})
		set_target_properties(lua PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${lua_BINARY_DIR}/lua)
	endif()
endif()
