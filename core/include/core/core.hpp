#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <cereal/archives/json.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>

#include <core/macros.hpp>
#include <core/starlightapi.hpp>
#include <gsl/gsl>

#include <core/utils/log.hpp>

namespace starlight::core {
struct STARLIGHTAPI Core {
    using LogManager = starlight::core::utils::LogManager;
    using LogType = starlight::core::utils::LogType;
    using LogConfigs = std::vector<starlight::core::utils::LogConfig>;

    constexpr const static int answer = 42;
    const SLC_CHAR* loggerName;
    std::unique_ptr<LogManager> logManager;
    Core() : loggerName("system") { logManager = std::make_unique<LogManager>(); }
    Core(LogConfigs&& logConfig) : loggerName("system") {
        logManager = std::make_unique<LogManager>(std::forward<LogConfigs>(logConfig));
    }
};

} // namespace starlight::core