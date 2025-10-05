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

class MJSDL_NODISCARD GPUGraphicsPipeline final {
    SDL_GPUGraphicsPipeline *item{};
    SDL_GPUDevice *_device{};

   public:
    MJSDL_NODISCARD GPUGraphicsPipeline() = default;
    MJSDL_NODISCARD GPUGraphicsPipeline(SDL_GPUGraphicsPipeline *native,
                                        SDL_GPUDevice *device)
        : item{native}, _device{device} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPUGraphicsPipeline(
        SDL_GPUDevice *device,
        const SDL_GPUGraphicsPipelineCreateInfo *createinfo, Guard guard = {})
        : _device{device} {
        item = SDL_CreateGPUGraphicsPipeline(device, createinfo);
        guard(item);
    }

    GPUGraphicsPipeline(const GPUGraphicsPipeline &) = delete;
    GPUGraphicsPipeline &operator=(const GPUGraphicsPipeline &) = delete;

    MJSDL_NODISCARD GPUGraphicsPipeline(GPUGraphicsPipeline &&other) noexcept {
        *this = std::move(other);
    }
    GPUGraphicsPipeline &operator=(GPUGraphicsPipeline &&other) noexcept {
        if (item) SDL_ReleaseGPUGraphicsPipeline(_device, item);
        item = std::exchange(other.item, nullptr);

        _device = std::exchange(other._device, decltype(_device){});

        return *this;
    }

    ~GPUGraphicsPipeline() {
        if (item) SDL_ReleaseGPUGraphicsPipeline(_device, item);
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
