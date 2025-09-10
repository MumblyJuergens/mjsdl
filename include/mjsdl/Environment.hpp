#pragma once

#include <SDL3/SDL_version.h>
#if SDL_VERSION_ATLEAST(3, 2, 0)

// This is a generated file!
// For contributions please consider changes in the "generator" directory.

#include <SDL3/SDL.h>

#include <utility>

#include "compat.hpp"
#include "guard.hpp"
#include "memory.hpp"

namespace mjsdl {

class MJSDL_NODISCARD Environment final {
    SDL_Environment *item{};

   public:
    MJSDL_NODISCARD Environment() = default;
    MJSDL_NODISCARD Environment(SDL_Environment *native) : item{native} {}

    template <typename Guard = MJSDL_GUARD_DEFAULT>
    MJSDL_NODISCARD Environment(bool populated, Guard guard = {}) {
        item = SDL_CreateEnvironment(populated);
        guard(item);
    }

    Environment(const Environment &) = delete;
    Environment &operator=(const Environment &) = delete;

    MJSDL_NODISCARD Environment(Environment &&other) noexcept {
        *this = std::move(other);
    }
    Environment &operator=(Environment &&other) noexcept {
        item = std::exchange(other.item, nullptr);

        return *this;
    }

    ~Environment() {
        if (item) SDL_DestroyEnvironment(item);
    }

    MJSDL_NODISCARD auto get() const noexcept { return item; }
    MJSDL_NODISCARD bool is_valid() const noexcept { return item; }
    MJSDL_NODISCARD auto release() noexcept {
        return std::exchange(item, nullptr);
    }

    // |            | //
    // | Extra Toys | //
    // V            V //

    MJSDL_NODISCARD const char *get_variable(const char *name) {
        return SDL_GetEnvironmentVariable(item, name);
    }

    MJSDL_NODISCARD auto get_variables() {
        char **result = SDL_GetEnvironmentVariables(item);
        return unique_sdlmem<char *>{result};
    }

    MJSDL_NODISCARD bool set_variable(const char *name, const char *value,
                                      bool overwrite) {
        return SDL_SetEnvironmentVariable(item, name, value, overwrite);
    }

    MJSDL_NODISCARD bool unset_variable(const char *name) {
        return SDL_UnsetEnvironmentVariable(item, name);
    }
};

}  // End of namespace mjsdl.

#endif
