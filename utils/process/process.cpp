// https://github.com/A5-/CSGO-External/tree/master/csgo-extern/memory
#include "../../include.h"

Process::Process()
{

}

Process::~Process()
{
	detach();
}

auto Process::attach(const std::string& str_process_name) -> bool
{
	detach();

	if (str_process_name.empty())
		return false;

	dw_process_id = get_process_id_by_name(str_process_name);
	if (!dw_process_id)
		return false;

	h_process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dw_process_id);
	if (!h_process)
		return false;

	if (DEBUG_MODE) std::cout << "process->Attach('" << str_process_name << "')" << std::endl;

	dw_module = get_module_base_address("ac_client.exe");
	if (DEBUG_MODE) std::cout << "process->GetModuleBaseAddress('ac_client.exe') = " << std::hex << dw_module << ";" << std::endl;

	return true;
}

auto Process::detach() -> void
{
	if (h_process) {
		CloseHandle(h_process);
		if (DEBUG_MODE) std::cout << "process->Detach()" << std::endl;
	}

	h_process = NULL;
	dw_process_id = NULL;
	dw_module = NULL;
}

auto Process::read(DWORD_PTR dw_address, LPVOID lp_buffer, DWORD_PTR dw_size) -> bool
{
	return (ReadProcessMemory(h_process, (LPCVOID)dw_address, lp_buffer, dw_size, NULL) == TRUE);
}

auto Process::write(DWORD_PTR dw_address, LPCVOID lpc_buffer, DWORD_PTR dw_size) -> bool
{
	return (WriteProcessMemory(h_process, (LPVOID)dw_address, lpc_buffer, dw_size, NULL) == TRUE);
}

auto Process::write_protected(DWORD_PTR dw_address, LPCVOID lpc_buffer, DWORD_PTR dw_size) -> bool
{
	DWORD_PTR oldProtect;
	if (VirtualProtectEx(h_process, (LPVOID)dw_address, dw_size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
		WriteProcessMemory(h_process, (LPVOID)dw_address, lpc_buffer, dw_size, NULL);
		VirtualProtectEx(h_process, (LPVOID)dw_address, dw_size, oldProtect, NULL);
		return true;
	}
	return false;
}

auto Process::get_window() -> HWND
{
	if (DEBUG_MODE) std::cout << "process->GetWindow() = " << h_window << std::endl;
	return h_window;
}

auto Process::set_window(HWND window_name) -> void
{
	h_window = window_name;
	if (DEBUG_MODE) std::cout << "process->SetWindow('" << window_name << "')" << std::endl;
}

auto Process::get_process_id_by_name(const std::string& str_process_name) -> DWORD
{
	HANDLE h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (h_snapshot == INVALID_HANDLE_VALUE)
		return NULL;

	PROCESSENTRY32 process_entry = { NULL };
	process_entry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(h_snapshot, &process_entry)) {
		CloseHandle(h_snapshot);
		return NULL;
	}

	do
	{
		if (str_process_name.compare(process_entry.szExeFile) == 0)
			break;

	} 
	while (Process32Next(h_snapshot, &process_entry));

	CloseHandle(h_snapshot);
	return process_entry.th32ProcessID;
}

auto Process::get_module_base_address(std::string str_module_name) -> DWORD
{
	HANDLE h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dw_process_id);
	if (h_snapshot == INVALID_HANDLE_VALUE) {
		if (DEBUG_MODE) std::cout << "Failed to take a snapshot of modules." << std::endl;
		CloseHandle(h_snapshot);
		return 0;
	}

	MODULEENTRY32 module_entry;
	module_entry.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(h_snapshot, &module_entry))
	{
		if (!strcmp(str_module_name.c_str(), module_entry.szModule)) {
			if (DEBUG_MODE) std::cout << "Found module " << module_entry.szModule << " with base address " << std::hex << std::uppercase << (DWORD)module_entry.modBaseAddr << std::endl;
			CloseHandle(h_snapshot);
			return (DWORD)module_entry.modBaseAddr;
		}
	}
	while (Module32Next(h_snapshot, &module_entry))
	{
		if (!strcmp(str_module_name.c_str(), module_entry.szModule))
		{
			if (DEBUG_MODE) std::cout << "Found module " << module_entry.szModule << " with base address " << std::hex << std::uppercase << (DWORD)module_entry.modBaseAddr << std::endl;
			CloseHandle(h_snapshot);
			return (DWORD)module_entry.modBaseAddr;
		}
	}
	if (DEBUG_MODE) std::cout << "Couldn't find " << str_module_name.c_str() << " module in module snapshot of the process." << std::endl;
	CloseHandle(h_snapshot);
	return false;
}

Process* process = new Process();