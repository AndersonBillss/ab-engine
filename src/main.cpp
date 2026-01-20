#include <webgpu/webgpu.h>
#include <iostream>

int main(int, char **)
{
  WGPUInstanceDescriptor desc = {};
  desc.nextInChain = nullptr;

  WGPUInstance instance = wgpuCreateInstance(&desc);

  if (!instance)
  {
    std::cerr << "Could not initialize WebGPU!" << std::endl;
    return 1;
  }

  std::cout << "WGPU instance: " << instance << std::endl;

  wgpuInstanceRelease(instance);

  return 0;
}