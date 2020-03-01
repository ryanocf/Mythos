#include "../include.h"

const char* state[] = { "[OFF]", "[ON]" };

Console::Console()
{
    if (Initialize() && DEBUG_MODE)
        std:: cout << "Console::Initialize() success!" << std::endl;
}

Console::~Console()
{

}

auto Console::Initialize() -> bool
{
    AllocConsole(); // enables the console
    const std::string alpha_numeric("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
    std::default_random_engine generator{ std::random_device{}() };
    const std::uniform_int_distribution<std::string::size_type>distribution{ 0, alpha_numeric.size() - 1 };
    std::string str(32, 0);
    for (auto& it : str) 
    {
        it = alpha_numeric[distribution(generator)]; // https://www.unknowncheats.me/forum/c-and-c-/374153-randomizing-window-names.html#post2683617
    }
    SetConsoleTitle(str.c_str());
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);

    return 1;
}

auto Console::Print(const char* fmt) -> void
{
    printf(fmt);
}

auto Console::Clear() -> void //https://stackoverflow.com/a/6487534
{
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}

Console* console = new Console();