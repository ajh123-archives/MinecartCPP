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
	${GLFW_INCLUDE_DIR}
	${GLAD_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}
	${ENTT_INCLUDE_DIR}
	${JSON_INCLUDE_DIR}
	${IMGUI_FILE_INCLUDE_DIR}
	# ${ZEP_INCLUDE_DIR}
)

target_link_libraries(Editor
	PRIVATE
	minecart
	glfw
	glad
	glm
	imgui
	lua
	EnTT::EnTT
	nlohmann_json
	imgui_file
	# Zep
	-static -static-libgcc -static-libstdc++
)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
	target_link_libraries(Editor "-framework IOKit")
	target_link_libraries(Editor "-framework Cocoa")
	target_link_libraries(Editor "-framework OpenGL")
endif()

set (source "${CMAKE_SOURCE_DIR}/resources")
set (destination "${CMAKE_BINARY_DIR}/resources")
add_custom_command(
	TARGET Editor POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
	DEPENDS ${destination}
	COMMENT "symbolic link resources folder from ${source} => ${destination}"
)