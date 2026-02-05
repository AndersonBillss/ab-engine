#include "canvasWindow.hpp"

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

void CanvasWindow::init(int width, int height, const std::string title)
{
    _width = width;
    _height = height;
    _title = title;
}

void CanvasWindow::destroy()
{
}
