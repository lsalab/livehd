//  This file is distributed under the BSD 3-Clause License. See LICENSE for details.
#pragma once

#include <vector>

#include "boost/multiprecision/cpp_int.hpp"
#include "absl/types/span.h"

class Lconst {
private:
  constexpr static int char_to_bits[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  constexpr static int char_to_val[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
  };
  constexpr static int char_to_shift_mode[256] = {
    /* 00 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 10 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 20 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 30 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 40 */ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    /* 50 */ 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
    /* 60 */ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
    /* 70 */ 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0,
    /* 80 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 90 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* A0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* B0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* C0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* D0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* E0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* F0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };

  static uint16_t read_bits(std::string_view txt);
  void process_ending(std::string_view txt, size_t pos);

protected:
  using Number=boost::multiprecision::cpp_int;

  bool     explicit_str;
  bool     explicit_sign;
  bool     explicit_bits;
  bool     sign;

  uint16_t bits;
  Number   num;

  void pyrope_bits(std::string *str) const;

  std::string_view skip_underscores(std::string_view txt) const;

  Lconst(bool str, bool a, bool b, bool c, uint16_t d, Number n) : explicit_str(str), explicit_sign(a), explicit_bits(b), sign(c), bits(d), num(n) {}

  uint16_t calc_bits() {
    uint16_t v=1;
    if (num) {
      v = msb(num)+1;
    }
    if (sign)
      v++;
    return v;
  }
  bool same_explicit_bits(const Lconst &o) const {
    bool s1 = explicit_bits && o.explicit_bits && bits == o.bits;
    bool s2 = !explicit_bits || !o.explicit_bits;

    return s1 || s2;
  }

public:
  using Container=std::vector<unsigned char>;

  Lconst(absl::Span<unsigned char> v);
  Lconst(const Container &v);
  Lconst(std::string_view txt);
  Lconst(uint64_t v);
  Lconst(uint64_t v, uint16_t bits);
  Lconst();

  Container serialize() const;

  void dump() const;

  Lconst add(const Lconst &o) const;

  bool     is_negative() const { return sign && num < 0; }
  bool     is_explicit_sign() const { return explicit_sign; }
  bool     is_explicit_bits() const { return explicit_bits; }
  bool     is_string() const { return explicit_str; }
  uint16_t get_bits() const { return bits; }
  Number get_num() const { return num; }
  Number get_num(uint16_t b) const {
    if (num >= 0 || sign) {
      assert(b>=bits);
      return num;
    } else {
      if (explicit_bits)
        b = bits;
      assert(!sign);
      Number max(1);
      max <<= b;
      max += num;
      return max;
    }
  }

  bool is_i() const;
  int to_i() const; // must fit in int or exception raised

  std::string to_yosys() const;
  std::string to_verilog() const;
  std::string to_string() const;
  std::string to_pyrope() const;

  // Operator list
  const Lconst operator+(const Lconst &other) const { return add(other); }
  const Lconst operator+(uint64_t other) const { return add(Lconst(other)); }

  bool operator==(const Lconst &other) const {
    auto b = std::max(bits,other.bits);
    return get_num(b) == other.get_num(b) && same_explicit_bits(other);
  }
  bool operator==(int other) const {
    if (bits>63)
      return false;
    return get_num(bits) == other;
  }
  bool operator!=(int other) const {
    if (bits>63)
      return true;
    return get_num(bits) != other;
  }
  bool operator!=(const Lconst &other) const {
    auto b = std::max(bits,other.bits);
    return get_num(b) != other.get_num(b) || !same_explicit_bits(other);
  }
  bool operator<(const Lconst &other) const {
    auto b = std::max(bits,other.bits);
    return get_num(b) < other.get_num(b);
  }
  bool operator<=(const Lconst &other) const {
    auto b = std::max(bits,other.bits);
    return get_num(b) <= other.get_num(b);
  }
  bool operator>(const Lconst &other) const {
    auto b = std::max(bits,other.bits);
    return get_num(b) > other.get_num(b);
  }
  bool operator>=(const Lconst &other) const {
    auto b = std::max(bits,other.bits);
    return get_num(b) >= other.get_num(b);
  }
};
