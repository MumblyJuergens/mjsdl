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

class MJSDL_NODISCARD Text final {
    TTF_Text *item{};

   public:
    MJSDL_NODISCARD Text() = default;
    MJSDL_NODISCARD Text(TTF_Text *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Text(TTF_TextEngine *engine, TTF_Font *font,
                         const char *text, size_t length, Guard guard = {}) {
        item = TTF_CreateText(engine, font, text, length);
        guard(item);
    }

    Text(const Text &) = delete;
    Text &operator=(const Text &) = delete;

    MJSDL_NODISCARD Text(Text &&other) noexcept { *this = std::move(other); }
    Text &operator=(Text &&other) noexcept {
        if (item) TTF_DestroyText(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Text() {
        if (item) TTF_DestroyText(item);
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
