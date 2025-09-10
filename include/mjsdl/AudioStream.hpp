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

class MJSDL_NODISCARD AudioStream final {
    SDL_AudioStream *item{};

   public:
    MJSDL_NODISCARD AudioStream() = default;
    MJSDL_NODISCARD AudioStream(SDL_AudioStream *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD AudioStream(const SDL_AudioSpec *src_spec,
                                const SDL_AudioSpec *dst_spec,
                                Guard guard = {}) {
        item = SDL_CreateAudioStream(src_spec, dst_spec);
        guard(item);
    }

    AudioStream(const AudioStream &) = delete;
    AudioStream &operator=(const AudioStream &) = delete;

    MJSDL_NODISCARD AudioStream(AudioStream &&other) noexcept {
        *this = std::move(other);
    }
    AudioStream &operator=(AudioStream &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~AudioStream() {
        if (item) SDL_DestroyAudioStream(item);
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
