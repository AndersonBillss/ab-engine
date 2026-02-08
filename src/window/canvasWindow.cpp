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

void CanvasWindow::pollEvents()
{
}

bool CanvasWindow::shouldClose()
{
    return false;
}

bool CanvasWindow::isInitialized()
{
    return true;
}
