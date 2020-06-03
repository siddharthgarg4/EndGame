//
//  DebugOverlay.cpp
//  EndGame
//
//  Created by Siddharth on 02/06/20.
//

#include "DebugOverlay.hpp"
#include <EndGame/Src/Application.hpp>
#include <EndGame/vendor/glfw/include/GLFW/glfw3.h>
#include <EndGame/vendor/imgui/include/imgui.h>
#include <EndGame/Src/SubSystems/DebugSubSystem/imguiOpenGlRender.h>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/KeyEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/MouseEvent.h>
#include <EndGame/Src/Core.h>

namespace EndGame {
        
    void DebugOverlay::onAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void DebugOverlay::onDetach() {}

    void DebugOverlay::onUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application &app = Application::getApplication();
        double glfwTime = glfwGetTime();
        static bool show = true;
        io.DeltaTime = frameTime > 0.0 ? (glfwTime - frameTime) : (1.0/60.0);
        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());
        frameTime = glfwTime;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(&show);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void DebugOverlay::onEvent(Event &event) {
        EventDispatcher dispatcher(event);
        //MARK: Key Events Callback
        //Key Pressed
        dispatcher.dispatch<KeyPressedEvent>([] (KeyPressedEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.KeysDown[event.getKeyCode()] = true;
            //modifiers
            io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
            io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
            io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
            io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
            return false;
        });
        //Key Released
        dispatcher.dispatch<KeyReleasedEvent>([] (KeyReleasedEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.KeysDown[event.getKeyCode()] = false;
            //modifiers
            io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
            io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
            io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
            io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
            return false;
        });
        //Key Typed
        dispatcher.dispatch<KeyTypedEvent>([] (KeyTypedEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.AddInputCharacter(event.getKeyCode());
            return false;
        });
        //MARK: Mouse Events Callback
        //Mouse Moved
        dispatcher.dispatch<MouseMovedEvent>([this] (MouseMovedEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.MousePos = ImVec2(event.getX(), event.getY());
            return false;
        });
        //Mouse Scrolled
        dispatcher.dispatch<MouseScrolledEvent>([this] (MouseScrolledEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseWheelH += event.getXOffset();
            io.MouseWheel += event.getYOffset();
            return false;
        });
        //Mouse Button Pressed
        dispatcher.dispatch<MouseButtonPressedEvent>([this] (MouseButtonPressedEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDown[event.getMouseButtonCode()] = true;
            return false;
        });
        //Mouse Button Released
        dispatcher.dispatch<MouseButtonReleasedEvent>([this] (MouseButtonReleasedEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.MouseDown[event.getMouseButtonCode()] = false;
            return false;
        });
        //MARK: Application Events Callback
        //Window Resize
        dispatcher.dispatch<WindowResizeEvent>([] (WindowResizeEvent &event) {
            ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());
            io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
            glViewport(0, 0, event.getWidth(), event.getHeight());
            return false;
        });
    }
}
