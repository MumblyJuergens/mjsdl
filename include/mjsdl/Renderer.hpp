#pragma once

#include <SDL3/SDL_version.h>
#if SDL_VERSION_ATLEAST(3, 2, 0)

// This is a generated file!
// For contributions please consider changes in the "generator" directory.

#include <SDL3/SDL.h>

#include <utility>

#include "GPUDevice.hpp"
#include "compat.hpp"
#include "guard.hpp"

namespace mjsdl {

class MJSDL_NODISCARD Renderer final {
    SDL_Renderer *item{};

   public:
    MJSDL_NODISCARD Renderer() = default;
    MJSDL_NODISCARD Renderer(SDL_Renderer *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Renderer(SDL_Window *window, const char *name,
                             Guard guard = {}) {
        item = SDL_CreateRenderer(window, name);
        guard(item);
    }

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;

    MJSDL_NODISCARD Renderer(Renderer &&other) noexcept {
        *this = std::move(other);
    }
    Renderer &operator=(Renderer &&other) noexcept {
        if (item) SDL_DestroyRenderer(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Renderer() {
        if (item) SDL_DestroyRenderer(item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

#if SDL_VERSION_ATLEAST(3, 4, 0)

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD static std::tuple<Renderer, GPUDevice> create_gpu_renderer(
        SDL_Window *window, SDL_GPUShaderFormat format_flags,
        Guard guard = {}) {
        SDL_GPUDevice *device = nullptr;
        SDL_Renderer *renderer =
            SDL_CreateGPURenderer(window, format_flags, &device);
        guard(renderer && device);
        return {Renderer{renderer}, GPUDevice{device}};
    }

    MJSDL_NODISCARD bool set_render_state(SDL_GPURenderState *state) {
        return SDL_SetRenderGPUState(item, state);
    }

#endif
};

}  // End of namespace mjsdl.

#endif
