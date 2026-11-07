#pragma once

#include <cstdint>
#include <cstdlib>
#include <utility>
#include <string>

namespace glpp {
    enum class ErrorCategory : std::uint8_t {
        Library,
        Context,
        Capability,
        Resource,
        OpenGL,
        Loader
    };

    enum class ErrorCode : std::uint16_t {
        LoaderNotInitialized,
        ContextNotActive,
        UnsupportedOpenGLVersion,
        UnsupportedFeature
    };

    constexpr ErrorCategory category(ErrorCode code) {
        switch (code) {
            case ErrorCode::LoaderNotInitialized:       return ErrorCategory::Loader;

            case ErrorCode::ContextNotActive:           return ErrorCategory::Context;

            case ErrorCode::UnsupportedOpenGLVersion:   return ErrorCategory::Capability;
            case ErrorCode::UnsupportedFeature:         return ErrorCategory::Capability;
        }

        std::abort();
    }

    struct Error {
        ErrorCode code;
        std::string message;

        Error(ErrorCode c, std::string m) : code(c), message(std::move(m)) {}

        ErrorCategory category() const {
            return glpp::category(code);
        }
    };
}