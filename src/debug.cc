#include <functional>
#include <iostream>

#ifdef DEBUG_LEVEL
constexpr auto g_debug_level = DEBUG_LEVEL;
#else
constexpr auto g_debug_level = 0;
#endif

#ifdef NDEBUG
constexpr auto g_ndebug = true;
#else
constexpr auto g_ndebug = false;
#endif

#define debug_console std::cout << __FILE__ << ':' << __LINE__ << ": "

template<std::size_t LEVEL>
void debug(std::function<void()> func) {
  if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
    std::cout << "\033[1;32mDEBUG\033[0m ";
    func();
  }
}

template<std::size_t LEVEL>
void warning(std::function<void()> func) {
  if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
    std::cout << "\033[1;33mWARNING\033[0m ";
    func();
  }
}

template<std::size_t LEVEL>
void fatal(std::function<void()> func) {
  if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
    std::cout << "\033[1;31mFATAL ERROR\033[0m ";
    func();
    ::exit(-1);
  }
}

template<std::size_t LEVEL>
void fatal(int error_code, std::function<void()> func) {
  if constexpr (!g_ndebug && (LEVEL <= g_debug_level)) {
    std::cout << "\033[1;31mFATAL ERROR\033[0m ";
    func();
    ::exit(error_code);
  }
}

int main() {
  debug<0>([]{debug_console << "Correct value is " << 65336 << '\n';});

  warning<0>(
      []{debug_console << "Maybe correct value is " << 65536 << '\n';});

  // fatal<0>(-1, [] {
  fatal<0>([]{debug_console << "Invalid value " << 65536 << '\n';});
}
