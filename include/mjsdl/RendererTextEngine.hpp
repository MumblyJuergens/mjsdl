#pragma once
#ifdef MJSDL_USING_TTF

#include <SDL3/SDL_version.h>
#if SDL_VERSION_ATLEAST(3, 2, 0)

// This is a generated file!
// For contributions please consider changes in the "generator" directory.

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <utility>

#include "compat.hpp"
#include "guard.hpp"

namespace mjsdl::ttf {

class MJSDL_NODISCARD RendererTextEngine final {
    TTF_TextEngine* item{};

   public:
    MJSDL_NODISCARD RendererTextEngine() = default;
    MJSDL_NODISCARD RendererTextEngine(TTF_TextEngine* native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD RendererTextEngine(SDL_Renderer* renderer,
                                       Guard guard = {}) {
        item = TTF_CreateRendererTextEngine(renderer);
        guard(item);
    }

    RendererTextEngine(const RendererTextEngine&) = delete;
    RendererTextEngine& operator=(const RendererTextEngine&) = delete;

    MJSDL_NODISCARD RendererTextEngine(RendererTextEngine&& other) noexcept {
        *this = std::move(other);
    }
    RendererTextEngine& operator=(RendererTextEngine&& other) noexcept {
        if (item) TTF_DestroyRendererTextEngine(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~RendererTextEngine() {
        if (item) TTF_DestroyRendererTextEngine(item);
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

}  // End of namespace mjsdl::ttf.

#endif
#endif
