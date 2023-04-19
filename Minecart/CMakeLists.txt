project(minecart)

# Find source files
file(GLOB MINECART_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MINECART_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(MINECART_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(minecart STATIC ${MINECART_SOURCES})
target_include_directories(minecart PUBLIC ${MINECART_INCLUDE_DIR})
target_include_directories(minecart PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(
	${GLFW_INCLUDE_DIR}
	${GLAD_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}
	${ENTT_INCLUDE_DIR}
	${JSON_INCLUDE_DIR}
)

target_link_libraries(minecart
	PRIVATE
	glfw
	glad
	glm
	imgui
	lua
	EnTT::EnTT
	nlohmann_json
)

set (source "${CMAKE_SOURCE_DIR}/resources")
set (destination "${CMAKE_BINARY_DIR}/resources")
add_custom_command(
	TARGET minecart POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
	DEPENDS ${destination}
	COMMENT "symbolic link resources folder from ${source} => ${destination}"
)