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

class MJSDL_NODISCARD GPUTransferBuffer final {
    SDL_GPUTransferBuffer *item{};
    SDL_GPUDevice *_device{};

   public:
    MJSDL_NODISCARD GPUTransferBuffer() = default;
    MJSDL_NODISCARD GPUTransferBuffer(SDL_GPUTransferBuffer *native,
                                      SDL_GPUDevice *device)
        : item{native}, _device{device} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPUTransferBuffer(
        SDL_GPUDevice *device,
        const SDL_GPUTransferBufferCreateInfo *createinfo, Guard guard = {})
        : _device{device} {
        item = SDL_CreateGPUTransferBuffer(device, createinfo);
        guard(item);
    }

    GPUTransferBuffer(const GPUTransferBuffer &) = delete;
    GPUTransferBuffer &operator=(const GPUTransferBuffer &) = delete;

    MJSDL_NODISCARD GPUTransferBuffer(GPUTransferBuffer &&other) noexcept {
        *this = std::move(other);
    }
    GPUTransferBuffer &operator=(GPUTransferBuffer &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        _device = std::exchange(other._device, decltype(_device){});

        return *this;
    }

    ~GPUTransferBuffer() {
        if (item) SDL_ReleaseGPUTransferBuffer(_device, item);
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
    MJSDL_NODISCARD GPUTransferBuffer(SDL_GPUDevice *device, Uint32 size,
                                      SDL_GPUTransferBufferUsage usage,
                                      Guard guard = {})
        : _device{device} {
        SDL_GPUTransferBufferCreateInfo info{};
        info.usage = usage;
        info.size = size;
        item = SDL_CreateGPUTransferBuffer(_device, &info);
        guard(item);
    }

    MJSDL_NODISCARD void *map(bool cycle) {
        return SDL_MapGPUTransferBuffer(_device, item, cycle);
    }
    void unmap() { SDL_UnmapGPUTransferBuffer(_device, item); }
};

}  // End of namespace mjsdl.

#endif
