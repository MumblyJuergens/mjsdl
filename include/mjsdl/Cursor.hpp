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

class MJSDL_NODISCARD Cursor final {
    SDL_Cursor *item{};

   public:
    MJSDL_NODISCARD Cursor() = default;
    MJSDL_NODISCARD Cursor(SDL_Cursor *native) : item{native} {}

    Cursor(const Cursor &) = delete;
    Cursor &operator=(const Cursor &) = delete;

    MJSDL_NODISCARD Cursor(Cursor &&other) noexcept {
        *this = std::move(other);
    }
    Cursor &operator=(Cursor &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Cursor() {
        if (item) SDL_DestroyCursor(item);
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
