#pragma once
#include <ntddk.h>

namespace ktl {
inline constexpr NTSTATUS KTL_INTERNAL_EXCEPTION{0xe4b544c};	//0xe'KTL' (UTF-8)
}