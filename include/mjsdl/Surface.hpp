#pragma once

#include <SDL3/SDL_version.h>
#if SDL_VERSION_ATLEAST(3, 2, 0)

// This is a generated file!
// For contributions please consider changes in the "generator" directory.

#include <SDL3/SDL.h>

#include <utility>

#include "compat.hpp"
#include "guard.hpp"

namespace mjsdl {

class MJSDL_NODISCARD Surface final {
    SDL_Surface *item{};

   public:
    MJSDL_NODISCARD Surface() = default;
    MJSDL_NODISCARD Surface(SDL_Surface *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Surface(int width, int height, SDL_PixelFormat format,
                            Guard guard = {}) {
        item = SDL_CreateSurface(width, height, format);
        guard(item);
    }

    Surface(const Surface &) = delete;
    Surface &operator=(const Surface &) = delete;

    MJSDL_NODISCARD Surface(Surface &&other) noexcept {
        *this = std::move(other);
    }
    Surface &operator=(Surface &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Surface() {
        if (item) SDL_DestroySurface(item);
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
