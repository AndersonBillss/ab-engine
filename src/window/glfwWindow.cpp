#include "glfwWindow.hpp"
#include <iostream>

GlfwWindow::~GlfwWindow()
{
    glfwTerminate();
}

GlfwWindow::GlfwWindow(int width, int height, std::string title) : Window(width, height, title)
{
    this->width_ = width;
    this->height_ = height;
    this->title_ = std::move(title);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }
    _win = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);
}

GlfwWindow::GlfwWindow(std::string title) : GlfwWindow(default_width, default_height, title) {}

void GlfwWindow::pollEvents()
{
    glfwPollEvents();
}

bool GlfwWindow::shouldClose()
{
    return glfwWindowShouldClose(_win);
}

bool GlfwWindow::isInitialized()
{
    return _win != nullptr;
}
