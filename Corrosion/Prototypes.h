#pragma once

#include <functional>
#include <cstdint>

#define MAKE_CONST_S32(b)     cast<Corrosion::const_s32_sig>((void*)b)
#define MAKE_IDENTITY(b)      cast<Corrosion::identity_sig >((void*)b)
#define MAKE_INCREMENT_S64(b) cast<Corrosion::increment_s64_sig>((void*)b)

using int64 = int64_t;
using int32 = int32_t;
using int16 = int16_t;
using int8 = int8_t;

using unt64 = uint64_t;
using unt32 = uint32_t;
using unt16 = uint16_t;
using unt8  = uint8_t;

namespace Corrosion {
	using const_s32_sig = int32();
	using const_s32 = std::function<int32()>;

	using identity_sig = int32(int32);
	using identity = std::function<identity_sig>;

	using increment_s64_sig = int64(int64);
	using increment_s64 = std::function<increment_s64_sig>;

	template<typename S>
	std::function<S> cast(void* f)
	{
		return static_cast<S*>(f);
	}

	const_s32 make_const_ret_func(int32_t val);
	identity make_identity();
	increment_s64 make_increment_64();
};

constexpr auto PREFIX_LOCK  = 0xF0;
constexpr auto PREFIX_REPNE = 0xF2;
constexpr auto PREFIX_REPNZ = 0xF2;
constexpr auto PREFIX_REP   = 0xF3;
constexpr auto PREFIX_REPE  = 0xF3;
constexpr auto PREFIX_REPZ  = 0xF3;

constexpr auto PREFIX_HINT_BRANCH_TAKEN     = 0x2E;
constexpr auto PREFIX_HINT_BRANCH_NOT_TAKEN = 0x3E;
