#include <glpp/diagnostics/log.hpp>
#include <glpp/diagnostics/detail/emit.hpp>

namespace glpp {
    namespace {
        LogCallback g_callback = nullptr;
        void* g_user = nullptr;
    }

    namespace detail {
        void emit_log(LogLevel level, std::string_view message) {
            if (g_callback) {
                g_callback(level, message, g_user);
            }
        }
    }

    void set_log_callback(LogCallback callback, void* user) {
        g_callback = callback;
        g_user = user;
    }
}