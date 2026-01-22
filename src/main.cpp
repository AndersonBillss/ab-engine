#include <webgpu/webgpu.h>
#include <iostream>

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

  wgpuInstanceRelease(instance);

  return 0;
}