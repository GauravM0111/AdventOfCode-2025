#include <iostream>
#include <array>
#include <string_view>
#include <format>

class Logger {
public:
  enum class Level {
    DEBUG,
    INFO,
    ERROR
  };
  static constexpr std::string_view getName(Level level) {
    switch (level) {
      case Level::DEBUG: return "";
      case Level::INFO:  return "[INFO]: ";
      case Level::ERROR: return "[ERROR]: ";
      default: return "";
    }
  }
  static constexpr Level min_level = Level::INFO;

  template<typename... Args>
  void log(Level level, std::format_string<Args...> fmt, Args&&... args) const {
    if (level < min_level) return;
    std::cout << getName(level) << std::format(fmt, std::forward<Args>(args)...);
  }

  template<typename... Args>
  void debug(std::format_string<Args...> fmt, Args&&... args) const { 
    log(Level::DEBUG, fmt, std::forward<Args>(args)...);
  }
  
  template<typename... Args>
  void info(std::format_string<Args...> fmt, Args&&... args) const { 
    log(Level::INFO, fmt, std::forward<Args>(args)...);
  }
  
  template<typename... Args>
  void error(std::format_string<Args...> fmt, Args&&... args) const { 
    log(Level::ERROR, fmt, std::forward<Args>(args)...);
  }
};
