#pragma once
#include <string>

class Window
{
public:
    virtual ~Window() = default;
    Window(int width, int height, std::string title)
        : width_(width), height_(height), title_(std::move(title)) {}

    Window(std::string title)
        : Window(default_width, default_height, std::move(title)) {}

    virtual void pollEvents() = 0;
    virtual bool shouldClose() = 0;
    virtual bool isInitialized() = 0;

protected:
    int width_ = 0;
    int height_ = 0;
    std::string title_;
    static constexpr int default_width = 800;
    static constexpr int default_height = 600;
};
