#pragma once
#include "window.hpp"
#include <string>

class CanvasWindow : public Window
{
public:
    ~CanvasWindow() override;
    CanvasWindow(int width, int height, std::string title);
    CanvasWindow(std::string title);
    void pollEvents() override;
    bool shouldClose() override;
    bool isInitialized() override;
};