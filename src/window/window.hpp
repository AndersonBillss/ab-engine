#include <string>

class Window
{
public:
    Window(int width, int height, const std::string title) { init(width, height, title); };
    Window(const std::string title) { init(default_width, default_height, title); };
    ~Window() { destroy(); };

    virtual void pollEvents() = 0;
    virtual bool shouldClose() = 0;

protected:
    virtual void init(int width, int height, const std::string title) = 0;
    virtual void destroy() = 0;
    static constexpr int default_width = 800;
    static constexpr int default_height = 600;
};
