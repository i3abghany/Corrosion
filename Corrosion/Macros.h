#pragma once

#include <cassert>

#define TODO() assert(false)
#define VERIFY_NOT_REACHED() assert(false)
#define VERIFY(expr) assert(expr)