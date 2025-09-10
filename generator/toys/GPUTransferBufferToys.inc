template <typename Guard = MJSDL_GUARD_DEFAULT>
MJSDL_NODISCARD GPUTransferBuffer(SDL_GPUDevice *device, Uint32 size, SDL_GPUTransferBufferUsage usage,
                                Guard guard = {})
    : _device{device}
{
    SDL_GPUTransferBufferCreateInfo info{};
    info.usage = usage;
    info.size = size;
    item = SDL_CreateGPUTransferBuffer(_device, &info);
    guard(item);
}

MJSDL_NODISCARD void *map(bool cycle) { return SDL_MapGPUTransferBuffer(_device, item, cycle); }
void unmap() { SDL_UnmapGPUTransferBuffer(_device, item); }

