#pragma once
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <string>

class GlfwWindow : public Window
{
public:
    ~GlfwWindow() override;
    GlfwWindow(int width, int height, std::string title);
    GlfwWindow(std::string title);
    void pollEvents() override;
    bool shouldClose() override;
    bool isInitialized() override;

private:
    GLFWwindow *_win;
};