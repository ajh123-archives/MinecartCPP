set(IMGUI_BRANCH "docking")
find_package(imgui QUIET) # QUIET or REQUIRED
if (NOT imgui_FOUND) # If there's none, fetch and build imgui
	include(FetchContent)
	FetchContent_Declare(
		imgui
		URL https://github.com/ocornut/imgui/archive/${IMGUI_BRANCH}.tar.gz
	)
	FetchContent_GetProperties(imgui)
	if (NOT imgui_POPULATED) # Have we downloaded imgui yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(imgui)

		# Configure ImGui build
		set(IMGUI_INCLUDE_DIR ${imgui_SOURCE_DIR})
		file(GLOB IMGUI_SOURCES ${IMGUI_INCLUDE_DIR}/*.cpp)
		file(GLOB IMGUI_HEADERS ${IMGUI_INCLUDE_DIR}/*.h)

		add_library(imgui STATIC ${IMGUI_SOURCES})
		set_target_properties(imgui PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${imgui_BINARY_DIR}/imgui)
	endif()
endif()
