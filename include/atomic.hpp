#pragma once
#include <basic_types.h>
#include <utility.hpp>

#include <ntddk.h>

namespace ktl {
namespace th {
bool interlocked_exchange(bool& target, bool new_value) {
  return InterlockedExchange8(
      reinterpret_cast<volatile char*>(addressof(target)),
      static_cast<char>(new_value));
}

void interlocked_swap(bool& lhs, bool& rhs) {
  bool old_lhs = lhs;
  interlocked_exchange(lhs, rhs);
  interlocked_exchange(rhs, old_lhs);
}

template <class Ty>
Ty* interlocked_exchange_pointer(Ty* const* ptr_place, Ty* new_ptr) noexcept {
  return static_cast<Ty*>(InterlockedExchangePointer(
      reinterpret_cast<volatile PVOID*>(const_cast<Ty**>(ptr_place)), new_ptr));
}

template <class Ty>
Ty* interlocked_compare_exchange_pointer(Ty* const* ptr_place,
                                         Ty* new_ptr,
                                         Ty* expected) noexcept {
  return static_cast<Ty*>(InterlockedCompareExchangePointer(
      reinterpret_cast<volatile PVOID*>(const_cast<Ty**>(ptr_place)), new_ptr,
      expected));
}

template <class Ty>
void interlocked_swap_pointer(Ty* const lhs, Ty* const rhs) noexcept {
  Ty* old_lhs = lhs;
  interlocked_exchange(lhs, rhs);
  interlocked_exchange(rhs, old_lhs);
}
}  // namespace th

template <typename IntegralTy, typename Ty>
static volatile IntegralTy* atomic_address_as(Ty& value) noexcept {
  static_assert(is_integral_v<IntegralTy>, "value must be integral");
  return &reinterpret_cast<volatile IntegralTy&>(value);
}

template <typename IntegralTy, typename Ty>
static const volatile IntegralTy* atomic_address_as(const Ty& value) noexcept {
  static_assert(is_integral_v<IntegralTy>, "value must be integral");
  return &reinterpret_cast<const volatile IntegralTy&>(value);
}

void read_write_barrier() noexcept {
  _ReadWriteBarrier();
}
}  // namespace ktl