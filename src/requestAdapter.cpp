#include "requestAdapter.hpp"

#ifdef WEBGPU_BACKEND_EMSCRIPTEN
#include <iostream>
#include <emscripten/emscripten.h>

WGPUAdapter requestAdapterSync(WGPUInstance instance, WGPURequestAdapterOptions const *options)
{
    struct UserData
    {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, char const *message, void *pUserData)
    {
        UserData &userData = *reinterpret_cast<UserData *>(pUserData);
        if (status == WGPURequestAdapterStatus_Success)
        {
            userData.adapter = adapter;
        }
        else
        {
            std::cout << "Could not get WebGPU adapter: " << message << std::endl;
        }
        userData.requestEnded = true;
    };

    wgpuInstanceRequestAdapter(
        instance,
        options,
        onAdapterRequestEnded,
        (void *)&userData);

    while (!userData.requestEnded)
    {
        emscripten_sleep(100);
    }

    return userData.adapter;
}

#else // WEBGPU_BACKEND_EMSCRIPTEN
#include <iostream>

std::ostream &operator<<(std::ostream &os, WGPUStringView stringView)
{
    for (size_t i = 0; i < stringView.length; i++)
    {
        os << stringView.data[i];
    }
    return os;
}

WGPUAdapter requestAdapterSync(WGPUInstance instance, WGPURequestAdapterOptions const *options)
{
    struct UserData
    {
        WGPUAdapter adapter = nullptr;
        bool requestEnded = false;
    };
    UserData userData;

    auto onAdapterRequestEnded = [](
                                     WGPURequestAdapterStatus status,
                                     WGPUAdapter adapter,
                                     WGPUStringView message,
                                     void *pUserData,
                                     void *userData2)
    {
        UserData &userData = *reinterpret_cast<UserData *>(pUserData);
        if (status == WGPURequestAdapterStatus_Success)
        {
            userData.adapter = adapter;
        }
        else
        {
            std::cout << "Could not get WebGPU adapter: " << message << std::endl;
        }
        userData.requestEnded = true;
    };
    WGPURequestAdapterOptions adapterOpts = {};
    adapterOpts.backendType = WGPUBackendType_D3D12;
    WGPURequestAdapterCallbackInfo info = {
        /* nextInChain */ nullptr,
        /* mode */ WGPUCallbackMode::WGPUCallbackMode_WaitAnyOnly,
        /* callback */ onAdapterRequestEnded,
        /* userdata 1 */ &userData,
        /* userdata 2 */ nullptr,
    };
    wgpuInstanceRequestAdapter(
        instance,
        &adapterOpts,
        info);

    return userData.adapter;
}
#endif //  WEBGPU_BACKEND_EMSCRIPTEN