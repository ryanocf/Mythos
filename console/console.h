#pragma once

class Console
{
public:
	Console();
	~Console();

	auto Initialize() -> bool;
	auto Print(const char* fmt) -> void;
	auto Clear() -> void;
};

extern Console* console;