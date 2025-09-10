#pragma once

#include <SDL3/SDL_stdinc.h>

#include <memory>

namespace mjsdl {

struct sdlmem_deleter {
    void operator()(void *p) { SDL_free(p); }
};

template <typename T>
using unique_sdlmem = std::unique_ptr<T, sdlmem_deleter>;

}  // End of namespace mjsdl.
