project(Editor)

# Find source files
file(GLOB MINECART_EDITOR_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MINECART_EDITOR_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(MINECART_EDITOR_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(Editor ${MINECART_EDITOR_SOURCES})
# set(raylib_VERBOSE 1)
target_include_directories(Editor PUBLIC ${MINECART_EDITOR_INCLUDE_DIR})
target_include_directories(Editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(
	minecart
	${RAYLIB_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
	${RLIMGUI_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}
)

target_link_libraries(Editor
    PRIVATE
    minecart
	raylib
	imgui
	rlimgui
	lua
	-static -static-libgcc -static-libstdc++
)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
	# Tell Emscripten to build an example.html file.
	set_target_properties(Editor PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
	target_link_libraries(Editor "-framework IOKit")
	target_link_libraries(Editor "-framework Cocoa")
	target_link_libraries(Editor "-framework OpenGL")
endif()
