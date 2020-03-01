#pragma once

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#define DIRECTINPUT_VERSION 0x0800

#include "../imgui/dx11/imgui_impl_win32.h"
#include "../imgui/dx11/imgui_impl_dx11.h"

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Render
{
public:
	auto Initialize() -> bool;

private:
	auto SetWindowBorderless() -> void;
	auto Shutdown() -> void;
	auto CreateDeviceD3D() -> bool;
	auto CleanupDeviceD3D() -> void;
	auto CreateRenderTarget() -> void;
	auto CleanupRenderTarget() -> void;
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	HWND h_Game;
	HWND h_hWnd;
	bool b_Shutdown = false;

private:
	WNDCLASSEX wc;

	ID3D11Device* g_pd3dDevice = NULL;
	ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
	IDXGISwapChain* g_pSwapChain = NULL;
	ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
};

extern Render* render;