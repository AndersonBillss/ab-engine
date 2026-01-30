#include <webgpu/webgpu.h>

using AdapterCallback = void (*)(WGPUAdapter adapter, void *userData);

void requestAdapterAsync(
    WGPUInstance instance,
    WGPURequestAdapterOptions const *options,
    AdapterCallback cb,
    void *userData);
