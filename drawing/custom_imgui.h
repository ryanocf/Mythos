#pragma once

class Custom_ImGui
{
public:
	auto Button(const char* label, const ImVec2& size_arg = ImVec2(0, 0)) -> bool;
	auto CustomBorder(int direction) -> void;
	auto Header(std::string label, int column) -> void;
	auto Keybind(const char* label, int key, const ImVec2& size_arg = ImVec2(0, 0)) -> bool;
	auto CaptureInputEvent(int& option) -> void;
};

extern Custom_ImGui* custom_imgui;