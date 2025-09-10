#pragma once

#include <SDL3/SDL_version.h>
#if SDL_VERSION_ATLEAST(3, 4, 0)

// This is a generated file!
// For contributions please consider changes in the "generator" directory.

#include <SDL3/SDL.h>

#include <utility>

#include "compat.hpp"
#include "guard.hpp"

namespace mjsdl {

class MJSDL_NODISCARD GPURenderState final {
    SDL_GPURenderState *item{};

   public:
    MJSDL_NODISCARD GPURenderState() = default;
    MJSDL_NODISCARD GPURenderState(SDL_GPURenderState *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD GPURenderState(SDL_Renderer *renderer,
                                   SDL_GPURenderStateCreateInfo *createinfo,
                                   Guard guard = {}) {
        item = SDL_CreateGPURenderState(renderer, createinfo);
        guard(item);
    }

    GPURenderState(const GPURenderState &) = delete;
    GPURenderState &operator=(const GPURenderState &) = delete;

    MJSDL_NODISCARD GPURenderState(GPURenderState &&other) noexcept {
        *this = std::move(other);
    }
    GPURenderState &operator=(GPURenderState &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~GPURenderState() {
        if (item) SDL_DestroyGPURenderState(item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

    MJSDL_NODISCARD bool set_fragment_uniforms(Uint32 slot_index,
                                               const void *data,
                                               Uint32 length) {
        return SDL_SetGPURenderStateFragmentUniforms(item, slot_index, data,
                                                     length);
    }
};

}  // End of namespace mjsdl.

#endif
