#ifndef MINECART_LOGGING_H
#define MINECART_LOGGING_H

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <string>
#include <imgui.h>

namespace minecart {
	namespace logging {
		int lua_PrintLog(lua_State *L);
		int lua_Print(lua_State *L);
		class Logger {
			protected:
				ImGuiTextBuffer     Buf;
				ImGuiTextFilter     Filter;
				ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
				bool                AutoScroll;  // Keep scrolling if already at the bottom.
			public:
				Logger();
				void Clear();
				void AddLog(int msgType, const char* fmt, va_list args);
				void AddLog(int msgType, const char* fmt, ...);
				void Draw(const char* title, bool* p_open = NULL);
		};
	}
}

#endif // MINECART_LOGGING_H
