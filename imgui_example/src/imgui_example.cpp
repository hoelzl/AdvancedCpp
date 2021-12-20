#include "imgui_example.hpp"

namespace imex {

void ImguiExampleApp::show_menu_bar()
{
    if (ImFrame::BeginMainMenuBar()) {
        if (ImFrame::BeginMenu("ImGui Demo")) {
            ImFrame::MenuItem("Show Info...", nullptr, &want_info_dialog_);
            ImFrame::MenuItem("Set Font...", nullptr, &want_set_ui_font_dialog_);

            if (ImFrame::MenuItem("Exit", nullptr)) {
                glfwSetWindowShouldClose(GetWindow(), true);
            }

            ImFrame::EndMenu();
        }
        ImFrame::EndMainMenuBar();
    }
}

void ImguiExampleApp::OnUpdate()
{
    show_menu_bar();

    if (want_info_dialog_) {
        show_info_dialog();
    }

    if (want_set_ui_font_dialog_) {
        show_ui_font_dialog();
    }
}

void ImguiExampleApp::set_size_and_position_for_new_window(
    float x, float y, ImGuiCond_ condition)
{
    ImGuiViewport const* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(
        ImVec2{main_viewport->WorkPos.x + 50, main_viewport->WorkPos.y + 50},
        condition);
    ImGui::SetNextWindowSize(ImVec2{x, y}, condition);
}

void ImguiExampleApp::show_info_dialog()
{
    set_size_and_position_for_new_window();

    if (!ImGui::Begin("Show Info", &want_info_dialog_)) {
        ImGui::End();
        return;
    }

    display_info_text();

    ImGui::End();
}

void ImguiExampleApp::display_info_text()
{
    ImGui::Text("ImGui Example");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::BulletText("Written by Dr. Matthias Hoelzl");
    ImGui::BulletText("Based on the ImFrame framework");
}

void ImguiExampleApp::show_ui_font_dialog()
{
    set_size_and_position_for_new_window();

    if (!ImGui::Begin("Set UI Font", &want_set_ui_font_dialog_)) {
        ImGui::End();
        return;
    }

    ImFrame::EnableCustomFont(true);

    display_font_type_widget();
    display_font_size_widget();

    ImGui::End();
}

void ImguiExampleApp::display_font_type_widget() const
{
    auto const fonts = std::array<char const*, 5>{
        "Carlito Regular", "OpenSans Regular", "OpenSans Semi-Bold", "Roboto Medium",
        "Roboto Regular"};

    auto font_type = ImFrame::GetCustomFontType();
    auto index = static_cast<int>(font_type);
    if (ImGui::Combo(
            "Font Name", &index, fonts.data(), static_cast<int>(fonts.size()))) {
        font_type = static_cast<ImFrame::FontType>(index);
        ImFrame::SetCustomFontType(font_type);
    }
}

void ImguiExampleApp::display_font_size_widget() const
{
    auto font_size = static_cast<ImU8>(ImFrame::GetCustomFontSize());
    ImU8 constexpr one = 1;
    if (ImGui::InputScalar(
            "Font Size", ImGuiDataType_U8, &font_size, &one, nullptr, "%u")) {
        font_size = std::clamp<ImU8>(font_size, 10, 48);
        ImFrame::SetCustomFontSize(static_cast<float>(font_size));
    }
}

} // namespace imex
