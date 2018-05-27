#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

#if STARLIGHT_DEBUG
#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
#define SPDLOG_FMT_EXTERNAL
#define SPDLOG_ENABLE_SYSLOG
#endif
#include <spdlog/spdlog.h>

#include <core/macros.hpp>

namespace starlight::core::utils {

// static inline void printGLError(const char* file, const char* func, int line) {
//     SUPPRESS_UNUSED(printGLError);
//     GLenum error = glGetError();
//     if (error != GL_NO_ERROR)
//         Debug() << "GL_ERROR: " << error << "\tFile: " << file << "\tFunction: " << func << "\tLine: " << line;
// }
// #define RINT_GL_ERROR() starlight::core::utils::printGLError(__FILE__, /*__FUNCTION__*/ "func", __LINE__)

// #if STARLIGHT_DEBUG
// #define Debug() std::cout << "DEBUG: "
// #else
// #include <sstream>
// #define Debug() std::stringstream() << "DEBUG: "
// #endif
// #define Info() std::cout << "INFO: "
// #define Warning() std::cerr << "WARNING: "
// #define Error() std::cerr << "ERROR: "

enum class STARLIGHTAPI LogLevel {
    error = spdlog::level::level_enum::err,
    warning = spdlog::level::level_enum::warn,
    info = spdlog::level::level_enum::info,
    debug = spdlog::level::level_enum::debug
};
enum class STARLIGHTAPI LogType { console, syslog, daily, rotate };

struct STARLIGHTAPI LogConfig {
    const SLC_CHAR* name;
    const SLC_CHAR* data;
    const LogLevel level;
    const LogType type;
};

using Config = const std::vector<LogConfig>;
using LoggerPTR = std::shared_ptr<spdlog::logger>;
using LevelEnum = spdlog::level::level_enum;

class STARLIGHTAPI LogManager {
  private:
    std::unordered_map<const SLC_CHAR*, LoggerPTR> loggers;

  public:
    constexpr const static std::array<const SLC_CHAR*, 2> REQUIRED_LOGGER_NAMES = {"default", "system"};
    LogManager() {
        spdlog::set_async_mode(512);
        // see https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
        spdlog::set_pattern("[%C-%m-%d %T][%l] %v");
        loggers.reserve(REQUIRED_LOGGER_NAMES.size());
        for (auto& logger : REQUIRED_LOGGER_NAMES) {
            loggers[logger] = spdlog::stdout_color_mt(logger);
#if STARLIGHT_DEBUG
            loggers[logger]->set_level((LevelEnum)LogLevel::debug);
#else
            loggers[logger]->set_level((LevelEnum)LogLevel::warning);
#endif
            loggers[logger]->flush_on(spdlog::level::err);
        }
    }
    LogManager(Config&& loggerConfig) {

#ifndef NDEBUG
        for (auto& logger : REQUIRED_LOGGER_NAMES)

            assert(std::find_if(loggerConfig.begin(), loggerConfig.end(),
                                [& logger = logger](const LogConfig& other) { return other.name == logger; })
                   != loggerConfig.end());
#endif

        spdlog::set_async_mode(512);
        loggers.reserve(loggerConfig.size());
        for (auto& item : loggerConfig) {
            switch (item.type) {
                case LogType::syslog:
                    loggers[item.name] = spdlog::syslog_logger(item.name);
                    break;
                case LogType::console:
                    loggers[item.name] = spdlog::stdout_color_mt(item.name);
                    break;
                case LogType::daily:
                    loggers[item.name] = spdlog::daily_logger_mt(item.name, item.data, 0, 0);
                    break;
                case LogType::rotate:
                    loggers[item.name] = spdlog::rotating_logger_mt(item.name, item.data, 1024*1024 * 10, 5);
                    break;
                default:
                    loggers[item.name] = spdlog::stdout_color_mt(item.name);
                    break;
            }
#if STARLIGHT_DEBUG
            loggers[item.name]->set_level((LevelEnum)LogLevel::debug);
#else
            loggers[item.name]->set_level((LevelEnum)item.level);
#endif
            loggers[item.name]->flush_on(spdlog::level::warn);
        }
    }
    ~LogManager() {
        for (auto& logger : loggers)
            logger.second->flush();
        loggers.clear();
    }

    LoggerPTR get(const SLC_CHAR* name) { return loggers[name]; }
    LoggerPTR get() { return get("default"); }
};

} // namespace starlight::core::utils
