#pragma once

class Process
{
public:
	Process();
	~Process();

	auto attach(const std::string& process_name) -> bool;
	auto detach() -> void;
	auto read(DWORD_PTR dw_address, LPVOID lp_buffer, DWORD_PTR dw_size) -> bool;
	auto write(DWORD_PTR dw_address, LPCVOID lpc_buffer, DWORD_PTR dw_size) -> bool;
	auto write_protected(DWORD_PTR dw_address, LPCVOID lp_buffer, DWORD_PTR dw_size) -> bool;
	auto get_window() -> HWND;
	auto set_window(HWND window_name) -> void;

	template<typename T>
	auto read(DWORD_PTR dw_address, const T& t_default = T()) -> T
	{
		T t_ret;
		if (!read(dw_address, &t_ret, sizeof(T)))
			return t_default;

		return t_ret;
	}

	template<typename T>
	auto read_multi(DWORD_PTR dw_address, std::vector<int> v3_offset, const T& tDefault = T()) -> T
	{
		T t_ret = dw_address;
		for (auto i = 0; i < v3_offset.size(); i++)
		{
			read(t_ret + v3_offset[i], &t_ret, sizeof(T));
		}
		return t_ret;
	}

	template<typename T>
	auto write(DWORD_PTR dw_address, const T& t_value) -> bool
	{
		return write(dw_address, &t_value, sizeof(T));
	}

	template<typename T>
	auto write_protected(DWORD_PTR dw_address, const T& t_value) -> bool
	{
		DWORD_PTR dw_old_protect;
		if (VirtualProtectEx(h_process, (LPVOID)dw_address, sizeof(T), PAGE_EXECUTE_READWRITE, &dw_old_protect)) {
			write(dw_address, &t_value, sizeof(T));
			VirtualProtectEx(h_process, (LPVOID)dw_address, sizeof(T), dw_old_protect, NULL);
			return true;
		}
		return false;
	}

	auto get_process_id_by_name(const std::string& str_process_name) -> DWORD;

private:
	auto get_module_base_address(std::string str_module_name) -> DWORD;

public:
	HANDLE h_process = NULL;
	DWORD dw_module = NULL;

private:
	DWORD dw_process_id = NULL;
	HWND h_window = NULL;
};

extern Process* process;