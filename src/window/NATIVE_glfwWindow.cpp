#include "NATIVE_glfwWindow.hpp"
#include <iostream>
#include <chrono>
#include <glfw3webgpu.h>

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

void GlfwWindow::setOnTick(Window::TickCallback cb)
{
    this->_onTick = cb;
}
void GlfwWindow::setOnExit(Window::ExitCallback cb)
{
    this->_onExit = cb;
}

void GlfwWindow::run()
{
    std::chrono::time_point last = std::chrono::steady_clock::now();
    while (!glfwWindowShouldClose(_win))
    {
        std::chrono::time_point now = std::chrono::steady_clock::now();
        double dtSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(now - last).count();
        last = now;
        glfwPollEvents();
        this->_onTick(dtSeconds);
    }
    this->_onExit();
}

bool GlfwWindow::isInitialized()
{
    return _win != nullptr;
}

WGPUSurface GlfwWindow::getSurface(WGPUInstance instance)
{
    return glfwCreateWindowWGPUSurface(instance, this->_win);
}
