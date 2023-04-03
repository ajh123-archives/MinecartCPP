#include <imgui.h>
#include <stdio.h>
#include <string>
#include <time.h> 
#include <raylib.h>
#include <regex>
#include "mc_logging.h"

minecart::logging::Logger::Logger() {
	this->AutoScroll = true;
	this->Clear();
}

void minecart::logging::Logger::Clear() {
	this->Buf.clear();
	this->LineOffsets.clear();
	this->LineOffsets.push_back(0);
}

void minecart::logging::Logger::AddLog(int msgType, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	this->AddLog(msgType, fmt, args);
	va_end(args);
}

void minecart::logging::Logger::AddLog(int msgType, const char* fmt, va_list args) {
	char timeStrBuffer[64] = { 0 };
	time_t now = time(NULL);
	struct tm *tm_info = localtime(&now);

	strftime(timeStrBuffer, sizeof(timeStrBuffer), "%Y-%m-%d %H:%M:%S", tm_info);
	std::string timeStr(timeStrBuffer);
	std::string level = "";

    switch (msgType) {
        case LOG_INFO: level = "\033[1;34m[INFO]\033[0m: "; break;
        case LOG_ERROR: level = "\033[1;33m[ERROR]\033[0m: "; break;
        case LOG_WARNING: level = "\033[1;33m[WARN]\033[0m: "; break;
        case LOG_DEBUG: level = "\033[1;37m[DEBUG]\033[0m: "; break;
        default: break;
    }
	std::string newFmt = "["+timeStr+"] "+level+std::string(fmt)+"\n";

	std::string guiFmt(newFmt.c_str());
	std::regex target("\033\\[[0-9;]*[A-Za-z]");
	guiFmt = std::regex_replace(guiFmt, target, "");

	int old_size = this->Buf.size();
	this->Buf.appendfv(guiFmt.c_str(), args);
	vprintf(newFmt.c_str(), args);
	for (int new_size = this->Buf.size(); old_size < new_size; old_size++)
		if (this->Buf[old_size] == '\n')
			this->LineOffsets.push_back(old_size + 1);
}

void minecart::logging::Logger::Draw(const char* title, bool* p_open) {
	ImGui::SetNextWindowSizeConstraints(ImVec2(400, 200), ImVec2(400, 200));
	if (!ImGui::Begin(title, p_open)) {
		ImGui::End();
		return;
	}

	// Options menu
	if (ImGui::BeginPopup("Options")) {
		ImGui::Checkbox("Auto-scroll", &this->AutoScroll);
		ImGui::EndPopup();
	}

	// Main window
	if (ImGui::Button("Options"))
		ImGui::OpenPopup("Options");
	ImGui::SameLine();
	bool clear = ImGui::Button("Clear");
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	this->Filter.Draw("Filter", -100.0f);

	ImGui::Separator();

	if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
		if (clear)
			Clear();
		if (copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = this->Buf.begin();
		const char* buf_end = this->Buf.end();
		if (this->Filter.IsActive()) {
			// In this example we don't use the clipper when Filter is enabled.
			// This is because we don't have random access to the result of our filter.
			// A real application processing logs with ten of thousands of entries may want to store the result of
			// search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
			for (int line_no = 0; line_no < this->LineOffsets.Size; line_no++) {
				const char* line_start = buf + this->LineOffsets[line_no];
				const char* line_end = (line_no + 1 < this->LineOffsets.Size) ? (buf + this->LineOffsets[line_no + 1] - 1) : buf_end;
				if (this->Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else {
			// The simplest and easy way to display the entire buffer:
			//   ImGui::TextUnformatted(buf_begin, buf_end);
			// And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
			// to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
			// within the visible area.
			// If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
			// on your side is recommended. Using ImGuiListClipper requires
			// - A) random access into your data
			// - B) items all being the  same height,
			// both of which we can handle since we have an array pointing to the beginning of each line of text.
			// When using the filter (in the block of code above) we don't have random access into the data to display
			// anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
			// it possible (and would be recommended if you want to search through tens of thousands of entries).
			ImGuiListClipper clipper;
			clipper.Begin(this->LineOffsets.Size);
			while (clipper.Step()) {
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++) {
					const char* line_start = buf + this->LineOffsets[line_no];
					const char* line_end = (line_no + 1 < this->LineOffsets.Size) ? (buf + this->LineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		// Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
		// Using a scrollbar or mouse-wheel will take away from the bottom edge.
		if (this->AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);
	}
	ImGui::EndChild();
	ImGui::End();
}
