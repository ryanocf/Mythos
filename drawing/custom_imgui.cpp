#include "../include.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"

// ImGui coding style just to not get confused

using namespace ImGui;

auto Custom_ImGui::Button(const char* label, const ImVec2& size_arg) -> bool
{
    int flags = 0;

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);
    size += ImVec2(0, 17);

    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    // Render
    const ImU32 col = GetColorU32((held && hovered) ? g.Style.Colors[ImGuiCol_ButtonActive] : hovered ? g.Style.Colors[ImGuiCol_ButtonHovered] : g.Style.Colors[ImGuiCol_Button]);
    //RenderNavHighlight(bb, id);
    //RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);
    window->DrawList->AddRectFilled(ImVec2(bb.Min.x, bb.Max.y - 5), ImVec2(bb.Max.x, bb.Max.y - 2), col, style.FrameRounding);
    RenderTextClipped(bb.Min + style.FramePadding, bb.Max - ImVec2(0, 12) - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
    return pressed;
}

auto Custom_ImGui::CustomBorder(int direction) -> void // directon: 0 = top, 1 = bottom , 2 = both, 3 = ignore column (ONLY DO ON BORDER WITH BIGGER HEIGHT! + NextColumn())
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;

    float thickness_draw = 1.0f;
    float thickness_layout;
    thickness_layout = 1.0f;
    if (direction == 2)
        thickness_layout = 2.0f;

    // Horizontal Separator
    float x1 = window->Pos.x;
    float x2 = window->Pos.x + window->Size.x;
    //if (!window->DC.GroupStack.empty())
      //  x1 += window->DC.Indent.x;

    ImGuiSeparatorFlags flags = (window->DC.LayoutType == ImGuiLayoutType_Horizontal) ? ImGuiSeparatorFlags_Vertical : ImGuiSeparatorFlags_Horizontal;
    flags &= ~ImGuiSeparatorFlags_SpanAllColumns;

    if (direction == 3)
        flags |= ImGuiSeparatorFlags_SpanAllColumns;

    ImGuiColumns* columns = (flags & ImGuiSeparatorFlags_SpanAllColumns) ? window->DC.CurrentColumns : NULL;
    
    if (columns)
        PushColumnsBackground();

    // We don't provide our width to the layout so that it doesn't get feed back into AutoFit
    const ImRect bb(ImVec2(x1, window->DC.CursorPos.y), ImVec2(x2, window->DC.CursorPos.y + thickness_draw));
    ItemSize(ImVec2(0.0f, thickness_layout));
    if (!ItemAdd(bb, 0)) {
        if (columns) {
            PopColumnsBackground();
            columns->LineMinY = window->DC.CursorPos.y;
        }
        return;
    }

    // Draw
    switch (direction)
    {
        case 0:
            window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), GetColorU32(ImGuiCol_Border));
            window->DrawList->AddLine(bb.Min + ImVec2(0, 1), ImVec2(bb.Max.x, bb.Min.y + 1), GetColorU32(ImGuiCol_Separator));
            break;

        case 1:
            window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), GetColorU32(ImGuiCol_Separator));
            window->DrawList->AddLine(bb.Min + ImVec2(0, 1), ImVec2(bb.Max.x, bb.Min.y + 1), GetColorU32(ImGuiCol_Border));
            break;

        case 2:
            window->DrawList->AddLine(bb.Min - ImVec2(0, 1), ImVec2(bb.Max.x, bb.Min.y - 1), GetColorU32(ImGuiCol_Separator));
            window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), GetColorU32(ImGuiCol_Border));
            window->DrawList->AddLine(bb.Min + ImVec2(0, 1), ImVec2(bb.Max.x, bb.Min.y + 1), GetColorU32(ImGuiCol_Separator));
            break;

        case 3:
            window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), GetColorU32(ImGuiCol_Separator));
            window->DrawList->AddLine(bb.Min + ImVec2(0, 1), ImVec2(bb.Max.x, bb.Min.y + 1), GetColorU32(ImGuiCol_Border));
            break;
    }

    if (columns)
    {
        PopColumnsBackground();
        columns->LineMinY = window->DC.CursorPos.y;
    }
}

auto Custom_ImGui::Header(std::string label, int column) -> void
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label.c_str());
    ImVec2 label_size = CalcTextSize(label.c_str(), NULL, true);

    float x1 = window->Pos.x;
    float x2 = window->Pos.x + window->Size.x;

    float default_h = label_size.y + style.FramePadding.y * 2.0f;

    if (column == 1)
        x2 = window->Pos.x + window->Size.x / 2;
    else if (column == 2)
        x1 = window->Pos.x + window->Size.x / 2;

    const ImRect bb(ImVec2(x1, window->DC.CursorPos.y), ImVec2(x2, window->DC.CursorPos.y));
    ItemSize(ImVec2(0.0f, default_h));
    if (!ItemAdd(bb, id))
        return;

    window->DrawList->AddLine(ImVec2(bb.Min.x + style.WindowPadding.x, bb.Min.y + default_h / 2), ImVec2(bb.Min.x + (bb.Max.x - bb.Min.x) / 2 - label_size.x - style.WindowPadding.x, bb.Min.y + default_h / 2), GetColorU32(ImGuiCol_TitleBg));
    window->DrawList->AddText(ImVec2(bb.Min.x + (bb.Max.x - bb.Min.x) / 2 - label_size.x / 2, bb.Min.y), GetColorU32(ImGuiCol_Text), label.c_str());
    window->DrawList->AddLine(ImVec2(bb.Min.x + (bb.Max.x - bb.Min.x) / 2 + label_size.x + style.WindowPadding.x, bb.Min.y + default_h / 2), ImVec2(bb.Max.x - style.WindowPadding.x, bb.Min.y + default_h / 2), GetColorU32(ImGuiCol_TitleBg));
}

auto Custom_ImGui::Keybind(const char* label, int i_key, const ImVec2& size_arg) -> bool
{
    int flags = 0;

    std::string key = utils->get_key_name(i_key);
    std::transform(key.begin(), key.end(), key.begin(), std::toupper);

    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    const ImVec2 key_size = CalcTextSize(key.c_str(), NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
        pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
    ImVec2 size = CalcItemSize(size_arg, max(key_size.x, label_size.x) + style.FramePadding.x * 2.0f, key_size.y + label_size.y + 1 + style.FramePadding.y * 2.0f);
    const ImRect bb(pos, pos + size);
    ItemSize(size, style.FramePadding.y);
    if (!ItemAdd(bb, id))
        return false;

    if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
        flags |= ImGuiButtonFlags_Repeat;
    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

    // Render
    const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
    RenderNavHighlight(bb, id);
    RenderFrame(bb.Min + ImVec2(0, label_size.y + 1), bb.Max, col, true, style.FrameRounding);
    RenderTextClipped(bb.Min, bb.Max, label, NULL, &label_size, ImVec2(0, 0), &bb);
    RenderTextClipped(bb.Min + ImVec2(0, label_size.y) + style.FramePadding, bb.Max - style.FramePadding, key.c_str(), NULL, &key_size, style.ButtonTextAlign, &bb);

    // Automatically close popups
    //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
    //    CloseCurrentPopup();

    IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
    return pressed;
}

auto Custom_ImGui::CaptureInputEvent(int &option) -> void // maybe not the greatest approach
{
    while (1)
    {
        for (auto i = 0; i < 256; i++) 
        {
            if ((i > 6 && i < 16) || (i > 18 && i < 48) || (i > 90))
                continue;

            if (GetAsyncKeyState(i) & 0x8000) {
                option = i;
                return;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

Custom_ImGui* custom_imgui = new Custom_ImGui();