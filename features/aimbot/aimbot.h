#pragma once

class Aimbot
{
public:
	auto start() -> void;
	auto get_closest_target_to_crosshair(DWORD_PTR dw_local_player) -> DWORD_PTR;

private:
	auto get_closest_target_to_position(DWORD_PTR dw_local_player) -> DWORD_PTR;

};

extern Aimbot* aimbot;