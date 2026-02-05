#include "window.hpp"
#include <string>

class CanvasWindow : public Window
{
public:
    void pollEvents() override;
    bool shouldClose() override;
    bool isInitialized() override;

protected:
    void init(int width, int height, const std::string title) override;
    void destroy() override;

private:
    int _width;
    int _height;
    std::string _title;
};