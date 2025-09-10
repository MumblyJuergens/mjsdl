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

class MJSDL_NODISCARD GPUShader final {
    SDL_GPUShader *item{};
    SDL_GPUDevice *_device{};

   public:
    MJSDL_NODISCARD GPUShader() = default;
    MJSDL_NODISCARD GPUShader(SDL_GPUShader *native, SDL_GPUDevice *device)
        : item{native}, _device{device} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPUShader(SDL_GPUDevice *device,
                              const SDL_GPUShaderCreateInfo *createinfo,
                              Guard guard = {})
        : _device{device} {
        item = SDL_CreateGPUShader(device, createinfo);
        guard(item);
    }

    GPUShader(const GPUShader &) = delete;
    GPUShader &operator=(const GPUShader &) = delete;

    MJSDL_NODISCARD GPUShader(GPUShader &&other) noexcept {
        *this = std::move(other);
    }
    GPUShader &operator=(GPUShader &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        _device = std::exchange(other._device, decltype(_device){});

        return *this;
    }

    ~GPUShader() {
        if (item) SDL_ReleaseGPUShader(_device, item);
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
