#pragma once

#include <SDL3/SDL_version.h>
#if SDL_VERSION_ATLEAST(3, 2, 0)

// This is a generated file!
// For contributions please consider changes in the "generator" directory.

#include <SDL3/SDL.h>
#include <SDL3/SDL_gpu.h>

#include <utility>

#include "compat.hpp"
#include "guard.hpp"

namespace mjsdl {

class MJSDL_NODISCARD GPUBuffer final {
    SDL_GPUBuffer *item{};
    SDL_GPUDevice *_device{};

   public:
    MJSDL_NODISCARD GPUBuffer() = default;
    MJSDL_NODISCARD GPUBuffer(SDL_GPUBuffer *native, SDL_GPUDevice *device)
        : item{native}, _device{device} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPUBuffer(SDL_GPUDevice *device,
                              const SDL_GPUBufferCreateInfo *createinfo,
                              Guard guard = {})
        : _device{device} {
        item = SDL_CreateGPUBuffer(device, createinfo);
        guard(item);
    }

    GPUBuffer(const GPUBuffer &) = delete;
    GPUBuffer &operator=(const GPUBuffer &) = delete;

    MJSDL_NODISCARD GPUBuffer(GPUBuffer &&other) noexcept {
        *this = std::move(other);
    }
    GPUBuffer &operator=(GPUBuffer &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        _device = std::exchange(other._device, decltype(_device){});

        return *this;
    }

    ~GPUBuffer() {
        if (item) SDL_ReleaseGPUBuffer(_device, item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPUBuffer(SDL_GPUDevice *device, Uint32 size,
                              SDL_GPUBufferUsageFlags usage, Guard guard = {})
        : _device{device} {
        SDL_GPUBufferCreateInfo info{};
        info.size = size;
        info.usage = usage;
        item = SDL_CreateGPUBuffer(device, &info);
        guard(item);
    }
};

}  // End of namespace mjsdl.

#endif
