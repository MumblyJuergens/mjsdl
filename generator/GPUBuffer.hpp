#pragma once

#include "guard.hpp"
#include <SDL3/SDL.h>
#include <utility>

namespace mjsdl
{

class [[nodiscard]] GPUBuffer final
{
    SDL_GPUBuffer *item{};
    SDL_GPUDevice *_device{};

  public:
    [[nodiscard]] GPUBuffer() = default;
    [[nodiscard]] GPUBuffer(SDL_GPUBuffer *native) : item{native} {}
    template <typename Guard = MJSDL_GUARD_DEFAULT>
    [[nodiscard]] GPUBuffer(SDL_GPUDevice *device, const SDL_GPUBufferCreateInfo *createinfo, Guard guard = {})
        : _device{device}
    {
        item = SDL_CreateGPUBuffer(device, createinfo);
        guard(item);
    }
    GPUBuffer(const GPUBuffer &) = delete;
    GPUBuffer &operator=(const GPUBuffer &) = delete;
    [[nodiscard]] GPUBuffer(GPUBuffer &&other) noexcept { *this = std::move(other); }
    GPUBuffer &operator=(GPUBuffer &&other) noexcept
    {
        item = std::exchange(other.item, nullptr);
        _device = std::exchange(other._device, (SDL_GPUDevice *){});
        return *this;
    }
    template <typename Guard = MJSDL_GUARD_DEFAULT>
    [[nodiscard]] GPUBuffer(SDL_GPUDevice *device, Uint32 size, SDL_GPUBufferUsageFlags usage, Guard guard = {})
        : _device{device}
    {
        SDL_GPUBufferCreateInfo info{};
        info.size = size;
        info.usage = usage;
        item = SDL_CreateGPUBuffer(device, &info);
        guard(item);
    }

    ~GPUBuffer()
    {
        if (item) SDL_ReleaseGPUBuffer(_device, item);
    }

    [[nodiscard]] auto get() const noexcept { return item; }
    [[nodiscard]] bool is_valid() const noexcept { return item; }
};

} // End of namespace mjsdl.
