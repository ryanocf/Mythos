#include "../include.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"

using namespace ImGui;

auto Drawing::initialize() -> void
{
    ImGui::SetNextWindowSize(ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("test", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_None | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);
    {
        ImGui::PushFont(font2);

        if (Options::b_esp_active)
            visuals->draw();

        if (aimbot->b_aim_fov_hovered) {
            ImVec2 cam;
            cam.x = GetSystemMetrics(SM_CXSCREEN) / 2;
            cam.y = GetSystemMetrics(SM_CYSCREEN) / 2;

            drawing->circle(cam, Options::f_aimbot_fov, ImVec4(0.9f, 0.9f, 0.9f, 1.0f), 1.0f, false, false);
        }

        ImGui::PopFont();
    }
    ImGui::End();
}

auto Drawing::text(ImVec2 v2_pos, std::string str_text, ImVec4 v4_col, bool b_outline) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    const char* text_end = str_text.c_str() + strlen(str_text.c_str());

    // Hide anything after a '##' string
    const char* text_display_end = FindRenderedTextEnd(str_text.c_str(), text_end);

    if (b_outline) {
        window->DrawList->AddText(g.Font, g.FontSize, v2_pos - ImVec2(1, 0), GetColorU32(ImVec4(0, 0, 0, 1)), str_text.c_str(), text_display_end);
        window->DrawList->AddText(g.Font, g.FontSize, v2_pos - ImVec2(0, 1), GetColorU32(ImVec4(0, 0, 0, 1)), str_text.c_str(), text_display_end);
        window->DrawList->AddText(g.Font, g.FontSize, v2_pos + ImVec2(1, 0), GetColorU32(ImVec4(0, 0, 0, 1)), str_text.c_str(), text_display_end);
        window->DrawList->AddText(g.Font, g.FontSize, v2_pos + ImVec2(0, 1), GetColorU32(ImVec4(0, 0, 0, 1)), str_text.c_str(), text_display_end);
    }
    window->DrawList->AddText(g.Font, g.FontSize, v2_pos, GetColorU32(v4_col), str_text.c_str(), text_display_end);
}

auto Drawing::line(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, float f_thickness) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    const ImRect line_bb(v2_pos, v2_pos + v2_size);

    window->DrawList->AddLine(ImVec2(line_bb.Min.x, line_bb.Min.y), ImVec2(line_bb.Max.x, line_bb.Max.y), GetColorU32(v4_col), f_thickness);
}

auto Drawing::line(RECT rect, ImVec4 v4_col, float f_thickness) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    const ImRect line_bb(ImVec2(rect.left, rect.top), ImVec2(rect.right, rect.bottom));

    window->DrawList->AddLine(ImVec2(line_bb.Min.x, line_bb.Min.y), ImVec2(line_bb.Max.x, line_bb.Max.y), GetColorU32(v4_col), f_thickness);
}

auto Drawing::rect(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, float f_thickness, bool b_outline, bool b_inline) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    const ImRect rect_bb(v2_pos, v2_pos + v2_size);

    if (b_outline) {
        window->DrawList->AddRect(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), GetColorU32(ImVec4(0, 0, 0, 1)), 0.0f, 15, f_thickness);
    }
    if (b_inline) {
        window->DrawList->AddRect(rect_bb.Min + ImVec2(1, 1), rect_bb.Max - ImVec2(1, 1), GetColorU32(ImVec4(0, 0, 0, 1)), 0.0f, 15, f_thickness);
    }
    window->DrawList->AddRect(rect_bb.Min, rect_bb.Max, GetColorU32(v4_col), 0.0f, 15, f_thickness);
}

auto Drawing::rect(RECT rect, ImVec4 v4_col, float f_thickness, bool b_outline, bool b_inline) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    const ImRect rect_bb(ImVec2(rect.left, rect.top), ImVec2(rect.right, rect.bottom));

    if (b_outline) {
        window->DrawList->AddRect(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), GetColorU32(ImVec4(0, 0, 0, 1)), 0.0f, 15, f_thickness);
    }
    if (b_inline) {
        window->DrawList->AddRect(rect_bb.Min + ImVec2(1, 1), rect_bb.Max - ImVec2(1, 1), GetColorU32(ImVec4(0, 0, 0, 1)), 0.0f, 15, f_thickness);
    }
    window->DrawList->AddRect(rect_bb.Min, rect_bb.Max, GetColorU32(v4_col), 0.0f, 15, f_thickness);
}

auto Drawing::filled_rect(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, bool b_outline) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    const ImRect rect_bb(v2_pos, v2_pos + v2_size);

    if (b_outline) {
        window->DrawList->AddRectFilled(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), GetColorU32(ImVec4(0, 0, 0, 1)), 0.0f);
    }
    window->DrawList->AddRectFilled(rect_bb.Min, rect_bb.Max, GetColorU32(v4_col), 0.0f);
}

auto Drawing::filled_rect(RECT rect, ImVec4 v4_col, bool b_outline) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    const ImRect rect_bb(ImVec2(rect.left, rect.top), ImVec2(rect.right, rect.bottom));

    if (b_outline) {
        window->DrawList->AddRectFilled(rect_bb.Min - ImVec2(1, 1), rect_bb.Max + ImVec2(1, 1), GetColorU32(ImVec4(0, 0, 0, 1)), 0.0f);
    }
    window->DrawList->AddRectFilled(rect_bb.Min, rect_bb.Max, GetColorU32(v4_col), 0.0f);
}

auto Drawing::circle(ImVec2 v2_pos, float f_radius, ImVec4 v4_col, float f_thickness, bool b_outline, bool b_inline) -> void
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;

    if (b_outline) {
        window->DrawList->AddCircle(v2_pos, f_radius + 1.0f, GetColorU32(ImVec4(0, 0, 0, 1)), (int)f_radius, f_thickness);
    }
    if (b_inline) {
        window->DrawList->AddCircle(v2_pos, f_radius - 1.0f, GetColorU32(ImVec4(0, 0, 0, 1)), (int)f_radius, f_thickness);
    }
    window->DrawList->AddCircle(v2_pos, f_radius, GetColorU32(v4_col), 50, f_thickness);
}

Drawing* drawing = new Drawing();