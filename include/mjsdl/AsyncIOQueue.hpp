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

class MJSDL_NODISCARD AsyncIOQueue final {
    SDL_AsyncIOQueue *item{};

   public:
    MJSDL_NODISCARD AsyncIOQueue() = default;
    MJSDL_NODISCARD AsyncIOQueue(SDL_AsyncIOQueue *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD AsyncIOQueue(Guard guard = {}) {
        item = SDL_CreateAsyncIOQueue();
        guard(item);
    }

    AsyncIOQueue(const AsyncIOQueue &) = delete;
    AsyncIOQueue &operator=(const AsyncIOQueue &) = delete;

    MJSDL_NODISCARD AsyncIOQueue(AsyncIOQueue &&other) noexcept {
        *this = std::move(other);
    }
    AsyncIOQueue &operator=(AsyncIOQueue &&other) noexcept {
        if (item) SDL_DestroyAsyncIOQueue(item);
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~AsyncIOQueue() {
        if (item) SDL_DestroyAsyncIOQueue(item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

    MJSDL_NODISCARD bool get_result(SDL_AsyncIOOutcome *outcome) {
        return SDL_GetAsyncIOResult(item, outcome);
    }

    MJSDL_NODISCARD bool wait_result(SDL_AsyncIOOutcome *outcome,
                                     Sint32 timeoutMS) {
        return SDL_WaitAsyncIOResult(item, outcome, timeoutMS);
    }
};

}  // End of namespace mjsdl.

#endif
