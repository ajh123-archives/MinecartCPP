set(ENTT_VERSION "v3.11.1")
find_package(entt QUIET) # QUIET or REQUIRED
if (NOT entt_FOUND) # If there's none, fetch and build entt
	include(FetchContent)
	FetchContent_Declare(
		entt
		URL https://github.com/skypjack/entt/archive/refs/tags/${ENTT_VERSION}.tar.gz
	)
	FetchContent_GetProperties(entt)
	if (NOT entt_POPULATED) # Have we downloaded entt yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(entt)
		set(ENTT_INCLUDE_NATVIS ON CACHE BOOL "" FORCE) # Inlude natives
		add_subdirectory(${entt_SOURCE_DIR} ${entt_BINARY_DIR})
		set(ENTT_INCLUDE_DIR ${entt_SOURCE_DIR}/src/entt)
	endif()
endif()
