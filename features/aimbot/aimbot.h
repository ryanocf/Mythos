#pragma once

class Aimbot
{
public:
	auto start() -> void;

private:
	auto get_closest_target_to_crosshair(DWORD_PTR dw_local_player)->DWORD_PTR;
	auto get_closest_target_to_position(DWORD_PTR dw_local_player) -> DWORD_PTR;

public:
	bool b_aim_fov_hovered = false;
};

extern Aimbot* aimbot;