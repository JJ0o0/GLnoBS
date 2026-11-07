#include "check.hpp"
#include <glpp/glpp.hpp>
#include <glpp/diagnostics/detail/emit.hpp>

namespace {
    void count(glpp::LogLevel, std::string_view, void* user) {
        *(static_cast<int*>(user)) += 1;
    }
}

int main() {
    int counter = 0;
    glpp::set_log_callback(count, &counter);

    glpp::detail::emit_log(glpp::LogLevel::Debug, "Testing");
    CHECK(counter == 1);

    glpp::set_log_callback(nullptr, nullptr);

    glpp::detail::emit_log(glpp::LogLevel::Debug, "Testing Nullptr");
    CHECK(counter == 1);
    return g_failures == 0 ? 0 : 1;
}