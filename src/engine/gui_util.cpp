#include "gui_util.h"

#include "../imgui/imgui.h"
namespace engine::gui {

void TextCentered(const char* text) {
    float windowWidth = ImGui::GetColumnWidth(ImGui::GetColumnIndex());
    float textWidth   = ImGui::CalcTextSize(text).x;

    // Set cursor to (WindowWidth - TextWidth) / 2
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text);
}

}
