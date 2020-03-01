#pragma once

class Drawing
{
public:
	auto initialize() -> void;
	auto text(ImVec2 v2_pos, std::string str_text, ImVec4 v4_col, bool b_outline) -> void;
	auto line(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, float f_thickness) -> void;
	auto line(RECT rect, ImVec4 v4_col, float f_thickness) -> void;
	auto rect(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, float f_thickness, bool b_outline, bool b_inline) -> void;
	auto rect(RECT rect, ImVec4 v4_col, float f_thickness, bool b_outline, bool b_inline) -> void;
	auto filled_rect(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, bool b_outline) -> void;
	auto filled_rect(RECT rect, ImVec4 v4_col, bool b_outline) -> void;
	auto circle(ImVec2 v2_pos, float f_radius, ImVec4 v4_col, float f_thickness, bool b_outline, bool b_inline) -> void;

public:
	ImFont* font1;
	ImFont* font2;
	ImFont* font3;
};

extern Drawing* drawing;