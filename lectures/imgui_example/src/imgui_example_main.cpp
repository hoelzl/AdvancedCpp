#include "imgui_example.hpp"

#ifdef IMFRAME_WINDOWS
#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

IMFRAME_MAIN(
    "ImGui Example", "Dear ImGui Example (via ImFrame)", imex::ImguiExampleApp)
