#pragma once

class Triggerbot
{
public:
	auto start() -> void;

private:
	auto shoot(DWORD_PTR dw_LocalPlayer) -> void;
	auto clear_name() -> void;

private:
	std::string str_player;
};

extern Triggerbot* triggerbot;