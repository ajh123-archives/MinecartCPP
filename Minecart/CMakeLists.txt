project(minecart)

# Find source files
file(GLOB MINECART_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MINECART_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(MINECART_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(minecart STATIC ${MINECART_SOURCES})
target_include_directories(minecart PUBLIC ${MINECART_INCLUDE_DIR})
target_include_directories(minecart PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(
	${RAYLIB_INCLUDE_DIR}
	${IMGUI_INCLUDE_DIR}
	${RLIMGUI_INCLUDE_DIR}
	${LUA_INCLUDE_DIR}
	${ENTT_INCLUDE_DIR}
	${JSON_INCLUDE_DIR}
)

target_link_libraries(minecart
	PRIVATE
	raylib
	imgui
	rlimgui
	lua
	EnTT::EnTT
	nlohmann_json
)
