#include "../include.h"

auto Utils::wstring_to_string(const std::wstring& wstring) -> std::string
{
    int slength = (int)wstring.length() + 1;
    int len = WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), slength, 0, 0, 0, 0);
    std::string r(len, '\0');
    WideCharToMultiByte(CP_ACP, 0, wstring.c_str(), slength, &r[0], len, 0, 0);
    return r;
}

auto Utils::get_key_name(unsigned int virtual_key) -> std::string
{
    if (virtual_key > 0 && virtual_key < 7 && virtual_key != 3)
        return mouse_keys[virtual_key - 1];

    if (virtual_key > 15 && virtual_key < 19)
        return special_keys[virtual_key - 16];

    byte keyboardState[256];
    GetKeyboardState(keyboardState);
    wchar_t buf[512];
    ToUnicode(virtual_key, 0, keyboardState, buf, 512, 0);
    return wstring_to_string(buf);
}

Utils* utils = new Utils();