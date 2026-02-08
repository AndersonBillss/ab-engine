#include "WEB_canvasWindow.hpp"
#include <emscripten/emscripten.h>

CanvasWindow::~CanvasWindow()
{
}

CanvasWindow::CanvasWindow(int width, int height, std::string title) : Window(width, height, title)
{
    this->width_ = width;
    this->height_ = height;
    this->title_ = std::move(title);
}

CanvasWindow::CanvasWindow(std::string title) : CanvasWindow(default_width, default_height, title) {}

void CanvasWindow::setOnTick(Window::TickCallback cb)
{
    this->_onTick = cb;
}

void CanvasWindow::setOnExit(Window::ExitCallback cb)
{
    this->_onExit = cb;
}

void CanvasWindow::run()
{
    em_arg_callback_func cb = [](void *data)
    {
        auto *self = static_cast<CanvasWindow *>(data);
        std::chrono::time_point now = std::chrono::steady_clock::now();
        double dtSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(now - self->_lastFrame).count();
        self->_lastFrame = now;
        self->_onTick(dtSeconds);
    };
    emscripten_set_main_loop_arg(cb, this, 0, 1);
}

bool CanvasWindow::isInitialized()
{
    return true;
}
