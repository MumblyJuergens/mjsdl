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

class MJSDL_NODISCARD GPUTexture final {
    SDL_GPUTexture *item{};
    SDL_GPUDevice *_device{};

   public:
    MJSDL_NODISCARD GPUTexture() = default;
    MJSDL_NODISCARD GPUTexture(SDL_GPUTexture *native, SDL_GPUDevice *device)
        : item{native}, _device{device} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPUTexture(SDL_GPUDevice *device,
                               const SDL_GPUTextureCreateInfo *createinfo,
                               Guard guard = {})
        : _device{device} {
        item = SDL_CreateGPUTexture(device, createinfo);
        guard(item);
    }

    GPUTexture(const GPUTexture &) = delete;
    GPUTexture &operator=(const GPUTexture &) = delete;

    MJSDL_NODISCARD GPUTexture(GPUTexture &&other) noexcept {
        *this = std::move(other);
    }
    GPUTexture &operator=(GPUTexture &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        _device = std::exchange(other._device, decltype(_device){});

        return *this;
    }

    ~GPUTexture() {
        if (item) SDL_ReleaseGPUTexture(_device, item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

    // none for this class :(
};

}  // End of namespace mjsdl.

#endif
