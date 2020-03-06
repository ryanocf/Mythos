#pragma once

class Console
{
public:
	Console();
	~Console();

	auto initialize() -> bool;
};

extern Console* console;