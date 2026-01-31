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
  WGPUAdapter adapter = requestAdapterSync(instance, &adapterOpts);
  std::cout << "Got adapter: " << adapter << std::endl;

  WGPULimits supportedLimits = {};
  supportedLimits.nextInChain = nullptr;

  bool success = wgpuAdapterGetLimits(adapter, &supportedLimits) == WGPUStatus_Success;

  if (success)
  {
    std::cout << "Adapter limits:" << std::endl;
    std::cout << " - maxTextureDimension1D: " << supportedLimits.maxTextureDimension1D << std::endl;
    std::cout << " - maxTextureDimension2D: " << supportedLimits.maxTextureDimension2D << std::endl;
    std::cout << " - maxTextureDimension3D: " << supportedLimits.maxTextureDimension3D << std::endl;
    std::cout << " - maxTextureArrayLayers: " << supportedLimits.maxTextureArrayLayers << std::endl;
  }
  wgpuInstanceRelease(instance);
  return 0;
}