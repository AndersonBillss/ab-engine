#include "glfwWindow.hpp"

void GlfwWindow::pollEvents()
{
    glfwPollEvents();
}

bool GlfwWindow::shouldClose()
{
    return glfwWindowShouldClose(_win);
}

void GlfwWindow::init(int width, int height, const std::string title)
{
    this->_width = width;
    this->_height = height;
    this->_title = std::move(title);
    _win = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);
}

bool GlfwWindow::isInitialized()
{
    return _win != nullptr;
}

void GlfwWindow::destroy()
{
    glfwTerminate();
}
