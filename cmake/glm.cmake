
set(GLM_BRANCH "master")
find_package(glm QUIET) # QUIET or REQUIRED
if (NOT glm_FOUND) # If there's none, fetch and build glm
	include(FetchContent)
	FetchContent_Declare(
		glm
		URL https://github.com/g-truc/glm/archive/${GLM_BRANCH}.tar.gz
	)
	FetchContent_GetProperties(glm)
	if (NOT glm_POPULATED) # Have we downloaded glm yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(glm)

		# Configure GLM build
		set(GLM_INCLUDE_DIR ${glm_SOURCE_DIR})

		option(BUILD_TESTING OFF)

		add_subdirectory(${glm_SOURCE_DIR})
	endif()
endif()
