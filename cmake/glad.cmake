set(GLAD_BRANCH "c")
find_package(glad QUIET) # QUIET or REQUIRED
if (NOT glad_FOUND) # If there's none, fetch and build glad
	include(FetchContent)
	FetchContent_Declare(
		glad
		URL https://github.com/Dav1dde/glad/archive/${GLAD_BRANCH}.tar.gz
	)
	FetchContent_GetProperties(glad)
	if (NOT glad_POPULATED) # Have we downloaded glad yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(glad)

		# Configure Glad build
		set(GLAD_INCLUDE_DIR ${glad_SOURCE_DIR}/include)
		file(GLOB GLAD_SOURCES ${glad_SOURCE_DIR}/src/*.c)
		file(GLOB GLAD_HEADERS ${GLAD_INCLUDE_DIR}/*.h)

		include_directories(
			glad
			${GLAD_INCLUDE_DIR}
		)

		add_library(glad STATIC ${GLAD_SOURCES})
		set_target_properties(glad PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${glad_BINARY_DIR}/glad)
	endif()
endif()
