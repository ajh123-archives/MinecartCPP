set(GLFW_BRANCH "master")
find_package(glfw QUIET) # QUIET or REQUIRED
if (NOT glfw_FOUND) # If there's none, fetch and build glfw
	include(FetchContent)
	FetchContent_Declare(
		glfw
		URL https://github.com/glfw/glfw/archive/${GLFW_BRANCH}.tar.gz
	)
	FetchContent_GetProperties(glfw)
	if (NOT glfw_POPULATED) # Have we downloaded glfw yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(glfw)

		# Configure GLFW build
		set(GLFW_INCLUDE_DIR ${glfw_SOURCE_DIR}/include)

		option(GLFW_BUILD_DOCS OFF)
		option(GLFW_BUILD_EXAMPLES OFF)
		option(GLFW_BUILD_TESTS OFF)
		option(GLFW_INSTALL OFF)

		add_subdirectory(${glfw_SOURCE_DIR})
	endif()
endif()
