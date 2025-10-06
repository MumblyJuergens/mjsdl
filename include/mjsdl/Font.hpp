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

class MJSDL_NODISCARD Font final {
    TTF_Font *item{};

   public:
    MJSDL_NODISCARD Font() = default;
    MJSDL_NODISCARD Font(TTF_Font *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Font(const char *file, float ptsize, Guard guard = {}) {
        item = TTF_OpenFont(file, ptsize);
        guard(item);
    }

    Font(const Font &) = delete;
    Font &operator=(const Font &) = delete;

    MJSDL_NODISCARD Font(Font &&other) noexcept { *this = std::move(other); }
    Font &operator=(Font &&other) noexcept {
        if (item) TTF_CloseFont(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Font() {
        if (item) TTF_CloseFont(item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Font(SDL_IOStream *src, bool closeio, float ptsize,
                         Guard guard = {}) {
        item = TTF_OpenFontIO(src, closeio, ptsize);
        guard(item);
    }
};

}  // End of namespace mjsdl::ttf.

#endif
#endif
