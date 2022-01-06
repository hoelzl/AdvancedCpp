#pragma once
#ifndef IMGUI_EXAMPLE_IMGUI_EXAMPLE_HPP
#define IMGUI_EXAMPLE_IMGUI_EXAMPLE_HPP

#include <ImFrame.h>

namespace imex {

class ImguiExampleApp final : public ImFrame::ImApp
{
public:
    explicit ImguiExampleApp(GLFWwindow* window) : ImFrame::ImApp{window} {}
    void OnUpdate() override;

private:
    bool want_info_dialog_{false};
    bool want_set_ui_font_dialog_{false};

    void show_menu_bar();
    void show_info_dialog();
    void show_ui_font_dialog();

    void display_font_type_widget() const;
    void display_font_size_widget() const;
    static void display_info_text();

    static void set_size_and_position_for_new_window(
        float x = 350.f, float y = 250.f,
        ImGuiCond_ condition = ImGuiCond_FirstUseEver);
};

} // namespace imex

#endif // IMGUI_EXAMPLE_IMGUI_EXAMPLE_HPP
