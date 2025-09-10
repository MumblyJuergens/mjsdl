#pragma once

#if __has_cpp_attribute(nodiscard)
#define MJSDL_NODISCARD [[nodiscard]]
#else
#define MJSDL_NODISCARD
#endif
