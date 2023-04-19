set(IMGUI_FILE_BRANCH "Lib_Only")
find_package(imgui_file QUIET) # QUIET or REQUIRED
if (NOT imgui_file_FOUND) # If there's none, fetch and build imgui_file
	include(FetchContent)
	FetchContent_Declare(
		imgui_file
		URL https://github.com/aiekick/ImGuiFileDialog/archive/${IMGUI_FILE_BRANCH}.tar.gz
	)
	FetchContent_GetProperties(imgui_file)
	if (NOT imgui_file_POPULATED) # Have we downloaded imgui_file yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(imgui_file)

		# Configure ImGui build
		set(IMGUI_FILE_INCLUDE_DIR ${imgui_file_SOURCE_DIR})
		file(GLOB IMGUI_FILE_SOURCES ${IMGUI_FILE_INCLUDE_DIR}/*.cpp)
		file(GLOB IMGUI_FILE_HEADERS ${IMGUI_FILE_INCLUDE_DIR}/*.h)

		include_directories(
			imgui_file
			${IMGUI_INCLUDE_DIR}
		)

		add_library(imgui_file STATIC ${IMGUI_FILE_SOURCES})
		set_target_properties(imgui_file PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${imgui_file_BINARY_DIR}/imgui_file)
	endif()
endif()
