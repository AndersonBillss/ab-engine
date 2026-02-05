#include "window.hpp"
#include <GLFW/glfw3.h>
#include <string>

class GlfwWindow : public Window
{
public:
    void pollEvents() override;
    bool shouldClose() override;
    bool isInitialized() override;

protected:
    void init(int width, int height, const std::string title) override;
    void destroy() override;

private:
    GLFWwindow *_win;
    int _width;
    int _height;
    std::string _title;
};