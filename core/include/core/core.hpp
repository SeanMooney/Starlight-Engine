#pragma once

#include <iostream>
#include <string>
#include <utility>

#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>

#include <gsl/gsl>

#include <core/starlightapi.hpp>

using SLC_UINT = uint_fast32_t;
using SLC_INT = int_fast32_t;
using SLC_UINT32 = uint32_t;
using SLC_INT32 = int32_t;
using SLC_LONG = int_fast64_t;
using SLC_FLOAT = float;
using SLC_DOUBLE = double;
using SLC_CHAR = u_char;

#if defined(STARLIGHT_DEBUG_OUTPUT) // define to enable addtional debug code
#define STARLIGHT_DEBUG 1
#else
#define STARLIGHT_DEBUG 0
#endif

// standard exception message creation.
#define THROW(msg) std::throw_with_nested(std::runtime_error(msg));

// suppress unused function/param
#define SUPPRESS_UNUSED(a) (void)a

#define STARLIGHT_OUTPUT_ARCHIVE cereal::BinaryOutputArchive
#define STARLIGHT_INPUT_ARCHIVE cereal::BinaryInputArchive

namespace starlight::core {
class STARLIGHTAPI Shared {
  public:
    constexpr const static int answer = 42;
};
} // namespace starlight::core