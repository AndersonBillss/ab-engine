#include <webgpu/webgpu.h>
#include <iostream>
#include "requestAdapter.hpp"

void onAdapterRequested(WGPUAdapter adapter, void *pInstance)
{
  WGPUInstance &instance = *reinterpret_cast<WGPUInstance *>(pInstance);

  std::cout << "Got adapter: " << adapter << std::endl;

  wgpuInstanceRelease(instance);
}

int main(int, char **)
{
  std::cout << "Hello, WebGPU!!" << std::endl;

  WGPUInstanceDescriptor desc = {};
  desc.nextInChain = nullptr;
  desc.requiredFeatureCount = 1;
  WGPUInstanceFeatureName features[] = {WGPUInstanceFeatureName_TimedWaitAny};
  desc.requiredFeatures = features;

  // We create the instance using this descriptor
  WGPUInstance instance = wgpuCreateInstance(&desc);

  if (!instance)
  {
    std::cerr << "Could not initialize WebGPU!" << std::endl;
    return 1;
  }

  std::cout << "Requesting adapter..." << std::endl;

  WGPURequestAdapterOptions adapterOpts = {};
  adapterOpts.nextInChain = nullptr;
  requestAdapterAsync(instance, &adapterOpts, onAdapterRequested, &instance);
  return 0;
}