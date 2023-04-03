#ifndef MINECART_LOGGING_H
#define MINECART_LOGGING_H

#include <string>
#include <imgui.h>

namespace minecart {
	namespace logging {
		class Logger {
			protected:
				ImGuiTextBuffer     Buf;
				ImGuiTextFilter     Filter;
				ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
				bool                AutoScroll;  // Keep scrolling if already at the bottom.
			public:
				Logger();
				void Clear();
				void AddLog(const char* fmt, ...);
				void Draw(const char* title, bool* p_open = NULL);
		};
	}
}

#endif // MINECART_LOGGING_H
