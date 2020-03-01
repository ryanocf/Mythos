#include "../include.h"

auto Render::Initialize() -> bool
{
    SetWindowBorderless();
    // Create application window
    wc = { sizeof(WNDCLASSEX), ACS_TRANSPARENT, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
    RegisterClassEx(&wc);
    h_hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE, wc.lpszClassName, _T(""), WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, wc.hInstance, NULL);
    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(h_hWnd, &margins);
    SetLayeredWindowAttributes(h_hWnd, 0, 1.0f, LWA_ALPHA);
    SetLayeredWindowAttributes(h_hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);

    // Initialize Direct3D
    if (!CreateDeviceD3D())
    {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(h_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(h_hWnd);

    SetForegroundWindow(h_hWnd);

    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    menu->init_style();

    ImGui_ImplWin32_Init(h_hWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    ImVec4 clear_color = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (b_Shutdown)
            break;

        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        drawing->initialize(); // create custom imgui window

        if (Options::b_menu_open)
        {
            menu->draw();
        }

        static bool isDown = false;
        static bool isClicked = false;
        if (GetAsyncKeyState(VK_INSERT)) {
            isClicked = false;
            isDown = true;
        }
        else if (!GetAsyncKeyState(VK_INSERT) && isDown) {
            isClicked = true;
            isDown = false;
        }
        else {
            isClicked = false;
            isDown = false;
        }

        if (isClicked) { // works on desktop maybe fix later
            Options::b_menu_open = !Options::b_menu_open;
            long style = GetWindowLongPtr(h_hWnd, GWL_EXSTYLE);
            if (Options::b_menu_open) {
                style &= ~WS_EX_LAYERED;
                SetWindowLongPtr(h_hWnd, GWL_EXSTYLE, style);
                SetForegroundWindow(h_hWnd);
            }
            else {
                style |= WS_EX_LAYERED;
                SetWindowLongPtr(h_hWnd, GWL_EXSTYLE, style);
                SetForegroundWindow(h_Game);
            }
        }

        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(0, 0);

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    Shutdown();
    return 0;
}

// https://devblogs.microsoft.com/oldnewthing/20100412-00/?p=14353
auto Render::SetWindowBorderless() -> void
{
    WINDOWPLACEMENT g_wpPrev;
    DWORD dwStyle = GetWindowLong(h_Game, GWL_STYLE);
    MONITORINFO mi = { sizeof(mi) };
    if (GetWindowPlacement(h_Game, &g_wpPrev) &&
        GetMonitorInfo(MonitorFromWindow(h_Game,
            MONITOR_DEFAULTTOPRIMARY), &mi)) {
        SetWindowLong(h_Game, GWL_STYLE,
            dwStyle & ~WS_OVERLAPPEDWINDOW);
        SetWindowPos(h_Game, HWND_TOP,
            mi.rcMonitor.left, mi.rcMonitor.top,
            mi.rcMonitor.right - mi.rcMonitor.left,
            mi.rcMonitor.bottom - mi.rcMonitor.top,
            SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
}

auto Render::Shutdown() -> void
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    CleanupDeviceD3D();
    DestroyWindow(h_hWnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    std::exit(0);
}

auto Render::CreateDeviceD3D() -> bool
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = h_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

auto Render::CleanupDeviceD3D() -> void
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

auto Render::CreateRenderTarget() -> void
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

auto Render::CleanupRenderTarget() -> void
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

LRESULT WINAPI Render::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application Render
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        default: break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

Render* render = new Render();