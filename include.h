#pragma once

#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 6001)
#pragma warning(disable : 6031)
#pragma warning(disable : 6387)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <WinUser.h>
#include <thread>
#include <chrono>
#include <string>
#include <functional>
#include <vector>
#include <array>
#include <iterator>
#include <TlHelp32.h>
#include <tchar.h>
#include <dinput.h>
#include <CommCtrl.h>
#include <random>
#include <algorithm>
#include <cctype>

#define DEBUG_MODE			TRUE

// utils/math
#include "utils/math/v2.h"
#include "utils/math/v3.h"
#include "utils/math/v4.h"
#include "utils/math/math.h"

// utils/process
#include "utils/process/process.h"

// utils
#include "utils/utils.h"

// imgui
#include "imgui/imgui.h"

// options
#include "options/offsets.h"
#include "options/options.h"

// render
#include "render/render.h"

// drawing
#include "drawing/drawing.h"
#include "drawing/custom_imgui.h"

// console
#include "console/console.h"

// menu
#include "menu/menu.h"

// features
#include "features/aimbot/aimbot.h"
#include "features/triggerbot/triggerbot.h"
#include "features/visuals/visuals.h"
#include "features/miscellaneous/miscellaneous.h"