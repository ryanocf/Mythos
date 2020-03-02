#include "include.h"

auto Initialize() -> void
{
    
}

auto Render() -> void
{
    render->Initialize();
}

auto Aimbot() -> void
{
    while (1)
    {
        // aimbot
        if (Options::b_aimbot_active)
            aimbot->start();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

auto Triggerbot() -> void
{
    while (1)
    {
        // triggerbot
        if (Options::b_triggerbot_active)
            triggerbot->start();

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

auto Misc() -> void
{
    while (1)
    {
        // misc
        if (Options::b_misc_unlimted_health) {
            misc->unlimited_health();
        }

        if (Options::b_misc_unlimited_ammo) {
            misc->unlimited_ammo();
        }

        if (Options::b_misc_no_recoil && !offsets->b_no_recoil) {
            misc->no_recoil(true);
            offsets->b_no_recoil = true;
        }
        else if (!Options::b_misc_no_recoil && offsets->b_no_recoil) {
            misc->no_recoil(false);
            offsets->b_no_recoil = false;
        }

        if (Options::b_misc_rapidfire) {
            misc->rapidfire();
        }

        if (Options::b_misc_force_duals) {
            misc->force_duals();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
    std::cout << "Waiting for Assault Cube..." << std::endl;

    while (!render->h_Game || !process->h_process)
    {
        render->h_Game = FindWindow(NULL, "AssaultCube");
        if (render->h_Game) {
            process->attach("ac_client.exe");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    Initialize();

    process->set_window(render->h_Game);
    SetForegroundWindow(render->h_Game);

    std::thread thread_render(Render); // namespace Render
    thread_render.detach();
    std::cout << "[THREAD] Render started!" << std::endl;

    std::thread thread_aimbot(Aimbot);
    thread_aimbot.detach();
    std::cout << "[THREAD] Aimbot started!" << std::endl;

    std::thread thread_trigger(Triggerbot);
    thread_trigger.detach();
    std::cout << "[THREAD] Triggerbot started!" << std::endl;

    std::thread thread_misc(Misc);
    thread_misc.detach();
    std::cout << "[THREAD] Misc started!" << std::endl;

    std::cout << "[THREAD] Main started!" << std::endl;

    bool b_active = true;
    while (1)
    {
        if (!IsWindow(render->h_Game))
            render->b_Shutdown = true;

        HWND h_Foreground = GetForegroundWindow();
        if (h_Foreground != render->h_Game && h_Foreground != render->h_hWnd) {
            if (!b_active) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // not leaking
                continue;
            }
            SetWindowPos(render->h_hWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            b_active = false;
        }
        else {
            if (b_active) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // not leaking
                continue;
            }
            SetWindowPos(render->h_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

            if (Options::b_menu_open)
                SetForegroundWindow(render->h_hWnd);
            
            b_active = true;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}