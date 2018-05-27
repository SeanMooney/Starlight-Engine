#pragma once
#include <cstdint>
using SLC_UINT = std::uint_fast32_t;
using SLC_INT = std::int_fast32_t;
using SLC_UINT32 = std::uint32_t;
using SLC_INT32 = std::int32_t;
using SLC_LONG = std::int_fast64_t;
using SLC_FLOAT = float;
using SLC_DOUBLE = double;
using SLC_CHAR = char;

#ifndef NDEBUG // define to enable addtional debug code
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
