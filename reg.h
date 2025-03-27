#pragma once

#include <functional>
#include <ostream>
#include <unordered_set>
#include <cstdint>

class RegBase {
protected:
  // c++20支持类内inline static成员初始化
  inline static std::unordered_set<RegBase *> allRegs;

public:
  virtual ~RegBase() = default;
  virtual void update() = 0;
  static void global_clock() {
    for (const auto &reg : allRegs) {
      reg->update();
    }
  }
};

template <typename T> class Reg : public RegBase {
private:
  T curr_val;
  T next_val;
  uint32_t w_cnt;

protected:
  T get_value() { return this->curr_val; }
  T get_next_value() { return this->next_val; }

public:
  Reg(T init) : curr_val(init), next_val(init), w_cnt(0) { allRegs.insert(this); }
  ~Reg() { allRegs.erase(this); }
  // 禁用拷贝
  Reg(const Reg &) = delete;
  Reg &operator=(const Reg &) = delete;
  // 禁用移动
  Reg(Reg &&) = delete;
  Reg &operator=(Reg &&) = delete;

void operator<<=(T new_val) {
    if (w_cnt > 0) {
        throw std::runtime_error("Multiple assignments in the same cycle are not allowed!");
    }
    
    if (next_val != new_val) {
        next_val = new_val;
        w_cnt++;
    }
}

void update() override {
    if (curr_val != next_val) {
        curr_val = next_val;
    }
    w_cnt = 0; // Reset write count for the next cycle
}

  operator T() const { return curr_val; }

  // 等于运算符（支持T和Reg<T>比较）
  bool operator==(const T &other) const noexcept { return curr_val == other; }

  bool operator==(const Reg<T> &other) const noexcept {
    return curr_val == other.curr_val;
  }

  bool operator<=>(const T &other) const noexcept { return curr_val <=> other; }
  bool operator<=>(const Reg<T> &other) const noexcept {
    return curr_val <=> other.curr_val;
  }

  // 不等于运算符（通过等于运算符实现）
  bool operator!=(const T &other) const noexcept { return !(*this == other); }

  bool operator!=(const Reg<T> &other) const noexcept {
    return !(*this == other);
  }

  // 类型安全的全局比较运算符
  friend bool operator==(const T &lhs, const Reg<T> &rhs) noexcept {
    return rhs == lhs; // 复用成员函数
  }

  friend bool operator!=(const T &lhs, const Reg<T> &rhs) noexcept {
    return rhs != lhs;
  }

  // 仅用于初始化
  Reg &operator=(const T val) noexcept {
    if (curr_val != val) {
      curr_val = val;
    }
    return *this;
  }

  // implement fmt::printf for Reg
  friend std::ostream &operator<<(std::ostream &os, const Reg<T> &reg) {
    return os << reg.curr_val;
  }
};