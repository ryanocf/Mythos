#pragma once

class Utils
{
public:
	auto wstring_to_string(const std::wstring& Str) -> std::string;
	auto get_key_name(unsigned int virtualKey) -> std::string;

private:
	std::array<std::string, 6> mouse_keys = {
		"LBUTTON",
		"RBUTTON",
		"",
		"MBUTTON",
		"XBUTTON1",
		"XBUTTON2"
	};

	std::array<std::string, 3> special_keys = {
		"SHIFT",
		"CTRL",
		"ALT"
	};
};

extern Utils* utils;