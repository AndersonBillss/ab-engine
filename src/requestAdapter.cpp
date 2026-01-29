#include "requestAdapter.hpp"
#include <iostream>

#ifdef WEBGPU_BACKEND_EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif // WEBGPU_BACKEND_EMSCRIPTEN

#ifndef WEBGPU_BACKEND_EMSCRIPTEN
std::ostream &operator<<(std::ostream &os, WGPUStringView stringView)
{
  for (size_t i = 0; i < stringView.length; i++)
  {
    os << stringView.data[i];
  }
  return os;
}
#endif // WEBGPU_BACKEND_EMSCRIPTEN

WGPUAdapter requestAdapterSync(WGPUInstance instance, WGPURequestAdapterOptions const *options)
{
  struct UserData
  {
    WGPUAdapter adapter = nullptr;
    bool requestEnded = false;
  };
  UserData userData;

#ifdef WEBGPU_BACKEND_EMSCRIPTEN
  auto onAdapterRequestEnded = [](

                                   WGPURequestAdapterStatus status,
                                   WGPUAdapterImpl *adapter,
                                   const char *message,
                                   void *pUserData)
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
#else  // WEBGPU_BACKEND_EMSCRIPTEN
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
#endif // WEBGPU_BACKEND_EMSCRIPTEN
  WGPURequestAdapterOptions adapterOpts = {};
#ifdef WEBGPU_BACKEND_EMSCRIPTEN
  wgpuInstanceRequestAdapter(
      instance /* equivalent of navigator.gpu */,
      options,
      onAdapterRequestEnded,
      (void *)&userData);
  while (!userData.requestEnded)
  {
    emscripten_sleep(100);
  }
#else
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
#endif // WEBGPU_BACKEND_EMSCRIPTEN

  return userData.adapter;
}