#pragma once
#include "window.hpp"
#include <string>

class CanvasWindow : public Window
{
public:
    ~CanvasWindow() override;
    CanvasWindow(int width, int height, std::string title);
    CanvasWindow(std::string title);
    
    void setOnTick(Window::TickCallback cb) override;
    void setOnExit(Window::ExitCallback cb) override;
    void run() override;
    bool isInitialized() override;
private:
    Window::TickCallback _onTick;
    Window::ExitCallback _onExit;
};