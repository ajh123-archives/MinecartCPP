set(RLIMGUI_BRANCH "main")
find_package(rlimgui QUIET) # QUIET or REQUIRED
if (NOT rlimgui_FOUND) # If there's none, fetch and build rlImGui
	include(FetchContent)
	FetchContent_Declare(
		rlimgui
		URL https://github.com/raylib-extras/rlImGui/archive/${RLIMGUI_BRANCH}.tar.gz
	)
	FetchContent_GetProperties(rlimgui)
	if (NOT rlimgui_POPULATED) # Have we downloaded rlImGui yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(rlimgui)

		# Configure rlImGui build
		set(RLIMGUI_INCLUDE_DIR ${rlimgui_SOURCE_DIR})
		file(GLOB RLIMGUI_SOURCES ${RLIMGUI_INCLUDE_DIR}/*.cpp)
		file(GLOB RLIMGUI_HEADERS ${RLIMGUI_SOURCES}/*.h)

		add_library(rlimgui STATIC ${RLIMGUI_SOURCES})
		set_target_properties(rlimgui PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${rlimgui_BINARY_DIR}/rlImGui)

		include_directories(
			${RAYLIB_INCLUDE_DIR}
			${IMGUI_INCLUDE_DIR}
		)

		target_link_libraries(rlimgui
			PRIVATE
			raylib
			imgui
		)
	endif()
endif()
