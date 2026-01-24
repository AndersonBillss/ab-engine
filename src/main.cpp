#include <webgpu/webgpu.h>
#include <iostream>
#include <emscripten/emscripten.h>

int main(int, char **)
{
  WGPUInstanceDescriptor desc = {};
  desc.nextInChain = nullptr;

// We create the instance using this descriptor
#ifdef WEBGPU_BACKEND_EMSCRIPTEN
  WGPUInstance instance = wgpuCreateInstance(nullptr);
#else  //  WEBGPU_BACKEND_EMSCRIPTEN
  WGPUInstance instance = wgpuCreateInstance(&desc);
#endif //  WEBGPU_BACKEND_EMSCRIPTEN

  if (!instance)
  {
    std::cerr << "Could not initialize WebGPU!" << std::endl;
    return 1;
  }

  std::cout << "WGPU instance: " << instance << std::endl;
  for (size_t i = 0; i < 1000; i++)
  {
    std::cout << "NUMBER " << i << std::endl;
  }

  size_t safetyCap = 5000;
  for (size_t i = 0; i < safetyCap; i++)
  {
    std::cout << "TEST" << i << std::endl;
    emscripten_sleep(5);
  }

  wgpuInstanceRelease(instance);

  return 0;
}