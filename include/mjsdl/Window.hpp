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

class MJSDL_NODISCARD Window final {
    SDL_Window *item{};

   public:
    MJSDL_NODISCARD Window() = default;
    MJSDL_NODISCARD Window(SDL_Window *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Window(const char *title, int w, int h,
                           SDL_WindowFlags flags, Guard guard = {}) {
        item = SDL_CreateWindow(title, w, h, flags);
        guard(item);
    }

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    MJSDL_NODISCARD Window(Window &&other) noexcept {
        *this = std::move(other);
    }
    Window &operator=(Window &&other) noexcept {
        if (item) SDL_DestroyWindow(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Window() {
        if (item) SDL_DestroyWindow(item);
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
