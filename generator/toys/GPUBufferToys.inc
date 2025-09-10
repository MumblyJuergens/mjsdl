template<typename Guard = MJSDL_GUARD_DEFAULT>
MJSDL_NODISCARD GPUBuffer(SDL_GPUDevice *device, Uint32 size, SDL_GPUBufferUsageFlags usage, Guard guard = {})
: _device{device}
{
    SDL_GPUBufferCreateInfo info{};
    info.size = size;
    info.usage = usage;
    item = SDL_CreateGPUBuffer(device, &info);
    guard(item);
}
 
