#include "glfwWindow.hpp"

void GlfwWindow::pollEvents()
{
    glfwPollEvents();
}

bool GlfwWindow::shouldClose()
{
    return glfwWindowShouldClose(win);
}

void GlfwWindow::init(int width, int height, const std::string title)
{
    this->_width = width;
    this->_height = height;
    this->_title = std::move(title);
    win = glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr);
}

void GlfwWindow::destroy()
{
    glfwTerminate();
}
