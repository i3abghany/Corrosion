#pragma once

#include <functional>
#include <cstdint>

#define MAKE_CONST_S32(b)     cast<Corrosion::const_s32_sig>((void*)b)
#define MAKE_IDENTITY(b)      cast<Corrosion::identity_sig >((void*)b)
#define MAKE_INCREMENT_S64(b) cast<Corrosion::increment_s64_sig>((void*)b)

namespace Corrosion {
	using const_s32_sig = int32_t();
	using const_s32 = std::function<int32_t()>;

	using identity_sig = int32_t(int32_t);
	using identity = std::function<identity_sig>;

	using increment_s64_sig = int64_t(int64_t);
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
