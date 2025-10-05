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

class MJSDL_NODISCARD GPUDevice final {
    SDL_GPUDevice *item{};

   public:
    MJSDL_NODISCARD GPUDevice() = default;
    MJSDL_NODISCARD GPUDevice(SDL_GPUDevice *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPUDevice(SDL_GPUShaderFormat format_flags, bool debug_mode,
                              const char *name, Guard guard = {}) {
        item = SDL_CreateGPUDevice(format_flags, debug_mode, name);
        guard(item);
    }

    GPUDevice(const GPUDevice &) = delete;
    GPUDevice &operator=(const GPUDevice &) = delete;

    MJSDL_NODISCARD GPUDevice(GPUDevice &&other) noexcept {
        *this = std::move(other);
    }
    GPUDevice &operator=(GPUDevice &&other) noexcept {
        if (item) SDL_DestroyGPUDevice(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~GPUDevice() {
        if (item) SDL_DestroyGPUDevice(item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

    MJSDL_NODISCARD static GPUDevice create_with_properties(
        SDL_PropertiesID props) {
        return GPUDevice{SDL_CreateGPUDeviceWithProperties(props)};
    }
};

}  // End of namespace mjsdl.

#endif
