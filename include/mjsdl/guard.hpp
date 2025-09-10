#pragma once

#include <SDL3/SDL_error.h>

#include <stdexcept>

#ifndef MJSDL_GUARD_DEFAULT
#define MJSDL_GUARD_DEFAULT mjsdl::guard_noop
#endif

namespace mjsdl {

struct guard_noop {
    void operator()(bool) {}
};

class ctor_error : public std::runtime_error {
   public:
    ctor_error(const char *errmsg) : std::runtime_error{errmsg} {}
};

struct guard_throws {
    void operator()(bool test) {
        if (test) throw ctor_error{SDL_GetError()};
    }
};

}  // End of namespace mjsdl.
