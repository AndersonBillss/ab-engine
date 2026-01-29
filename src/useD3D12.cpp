#include "useD3D12.hpp"
#include <dawn/native/DawnNative.h>
#include <webgpu/webgpu.h>
#include <iostream>

bool useD3D12()
{
    const WGPURequestAdapterOptions opts = {
        /*nextInChain*/ nullptr,
        /*featureLevel*/ WGPUFeatureLevel::WGPUFeatureLevel_Undefined,
        /*powerPreference*/ WGPUPowerPreference::WGPUPowerPreference_Undefined,
        /*forceFallbackAdapter*/ 0,
        /*backendType*/ WGPUBackendType_D3D12,
        /*compatibleSurface*/ nullptr
    };
    dawn::native::Instance instance;
    std::vector<dawn::native::Adapter> adapters = instance.EnumerateAdapters(&opts);
    std::cout << adapters.size() << std::endl;
    return false;
}