#include "requestAdapter.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &os, WGPUStringView stringView)
{
    for (size_t i = 0; i < stringView.length; i++)
    {
        os << stringView.data[i];
    }
    return os;
}

void requestAdapterAsync(
    WGPUInstance instance,
    WGPURequestAdapterOptions const *options,
    AdapterCallback cb,
    void *data)
{
    struct UserData
    {
        bool done;
        AdapterCallback cb;
        void *data;
    };
    UserData userData;
    userData.cb = cb;
    userData.data = data;

    auto onAdapterRequestEnded = [](
                                     WGPURequestAdapterStatus status,
                                     WGPUAdapter adapter,
                                     WGPUStringView message,
                                     void *pUserData,
                                     void *_)
    {
        UserData &userData = *reinterpret_cast<UserData *>(pUserData);
        if (status == WGPURequestAdapterStatus_Success)
        {
            userData.done = true;
            userData.cb(adapter, userData.data);
        }
        else
        {
            std::cout << "Could not get WebGPU adapter: " << message << std::endl;
        }
    };
    WGPURequestAdapterOptions adapterOpts = {};
#ifndef WEBGPU_BACKEND_EMSCRIPTEN
    adapterOpts.backendType = WGPUBackendType_D3D12;
#endif // !WEBGPU_BACKEND_EMSCRIPTEN
    WGPURequestAdapterCallbackInfo info = {
        /* nextInChain */ nullptr,
        /* mode */ WGPUCallbackMode::WGPUCallbackMode_WaitAnyOnly,
        /* callback */ onAdapterRequestEnded,
        /* userdata 1 */ &userData,
        /* userdata 2 */ nullptr,
    };
    WGPUFuture f = wgpuInstanceRequestAdapter(
        instance,
        &adapterOpts,
        info);
    WGPUFutureWaitInfo waitInfo = {f, 0};

    wgpuInstanceWaitAny(instance, 1, &waitInfo, UINT64_MAX);
}