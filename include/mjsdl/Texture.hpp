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

class MJSDL_NODISCARD Texture final {
    SDL_Texture *item{};

   public:
    MJSDL_NODISCARD Texture() = default;
    MJSDL_NODISCARD Texture(SDL_Texture *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Texture(SDL_Renderer *renderer, SDL_PixelFormat format,
                            SDL_TextureAccess access, int w, int h,
                            Guard guard = {}) {
        item = SDL_CreateTexture(renderer, format, access, w, h);
        guard(item);
    }

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    MJSDL_NODISCARD Texture(Texture &&other) noexcept {
        *this = std::move(other);
    }
    Texture &operator=(Texture &&other) noexcept {
        if (item) SDL_DestroyTexture(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Texture() {
        if (item) SDL_DestroyTexture(item);
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
