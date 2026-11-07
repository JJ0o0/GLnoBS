#include "check.hpp"
#include <glpp/glpp.hpp>

int main() {
    const glpp::Error err(glpp::ErrorCode::ContextNotActive, "No Context");

    CHECK(err.code == glpp::ErrorCode::ContextNotActive);
    CHECK(err.message == "No Context");
    CHECK(err.category() == glpp::ErrorCategory::Context);

    return g_failures == 0 ? 0 : 1;
}