#pragma once

class Menu {
public:
	auto draw() -> void;
	auto init_style() -> void;

private:
	template<size_t T>
	auto render_tabs(const char* (&names)[T], int& u_active, ImVec2 v2_size, bool b_sameline)  -> void;
	auto render_aim() -> void;
	auto render_esp() -> void;
	auto render_misc() -> void;
	auto render_config() -> void;
};

extern Menu* menu;