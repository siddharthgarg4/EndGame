//
//  DebugOverlay.cpp
//  EndGame
//
//  Created by Siddharth on 02/06/20.
//

#include "DebugOverlay.hpp"
#include <GLFW/glfw3.h>
#include <imgui/include/imgui.h>
#include <EndGame/Src/SubSystems/DebugSubSystem/ImguiBuild.h>
#include <EndGame/Src/Application.hpp>

namespace EndGame {
        
    void DebugOverlay::onAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        Application &app = Application::getApplication();
        GLFWwindow *nativeWindow = static_cast<GLFWwindow *>(app.getWindow().getNativeWindow());
        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(nativeWindow, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void DebugOverlay::onDetach() {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void DebugOverlay::onImguiRender() {
        static bool showDemoWindow = true;
        ImGui::ShowDemoWindow(&showDemoWindow);
    }

    void DebugOverlay::preImguiRender() {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void DebugOverlay::postImguiRender() {
        ImGuiIO &io = ImGui::GetIO();
        Window &window = Application::getApplication().getWindow();
        io.DisplaySize = ImVec2(window.getWidth(), window.getHeight());
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}
