#include <webgpu/webgpu.h>
#include <iostream>
#include "requestAdapter.hpp"

#ifndef WEBGPU_BACKEND_EMSCRIPTEN 
#include "useD3D12.hpp"
#endif // !WEBGPU_BACKEND_EMSCRIPTEN

int main(int, char **)
{
  std::cout << "Hello, WebGPU!!" << std::endl;

  #ifndef WEBGPU_BACKEND_EMSCRIPTEN 
    useD3D12();
  #endif // !WEBGPU_BACKEND_EMSCRIPTEN

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

  std::cout << "Requesting adapter..." << std::endl;

  WGPURequestAdapterOptions adapterOpts = {};
  adapterOpts.nextInChain = nullptr;
  WGPUAdapter adapter = requestAdapterSync(instance, &adapterOpts);

  std::cout << "Got adapter: " << adapter << std::endl;

  wgpuInstanceRelease(instance);

  return 0;
}