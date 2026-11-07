#pragma once

#include <glpp/diagnostics/log.hpp>
#include <string_view>

namespace glpp::detail {
    void emit_log(LogLevel level, std::string_view message);
}