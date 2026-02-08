#include "canvasWindow.hpp"

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

void CanvasWindow::setOnExit(Window::ExitCallback cb) {
    this->_onExit = cb;
}

void CanvasWindow::run()
{
    this->_onTick(0);
    this->_onExit();
}

void CanvasWindow::setOnTick(Window::TickCallback cb) {
    this->_onTick = cb;
}

bool CanvasWindow::isInitialized()
{
    return true;
}
