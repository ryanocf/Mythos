#include "../include.h"

Console::Console()
{
    if (initialize() && DEBUG_MODE)
        std:: cout << "Console::Initialize() success!" << std::endl;
}

Console::~Console()
{

}

auto Console::initialize() -> bool
{
    AllocConsole(); // enables the console
    const std::string alpha_numeric("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
    std::default_random_engine generator{ std::random_device{}() };
    const std::uniform_int_distribution<std::string::size_type>distribution{ 0, alpha_numeric.size() - 1 };
    std::string str(32, 0);
    for (auto& it : str) 
    {
        it = alpha_numeric[distribution(generator)]; // https://www.unknowncheats.me/forum/c-and-c-/374153-randomizing-window-names.html#post2683617 for the memes
    }
    SetConsoleTitle(str.c_str());
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);

    return true;
}

Console* console = new Console();