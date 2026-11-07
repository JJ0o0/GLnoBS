#include "check.hpp"
#include <glpp/glpp.hpp>

int main() {
    glpp::Result<int> ok(42);
    CHECK(ok.has_value());
    CHECK(ok.value() == 42);

    const glpp::Result<int> cr(7);
    CHECK(cr.value() == 7);

    glpp::Result<int> fail(glpp::Error(glpp::ErrorCode::ContextNotActive, "No Context"));
    CHECK(!fail.has_value());
    CHECK(fail.error().code == glpp::ErrorCode::ContextNotActive);
    CHECK(fail.error().message == "No Context");

    auto ok_void = glpp::Result<void>::success();
    CHECK(ok_void.has_value());

    glpp::Result<void> fail_void(glpp::Error(glpp::ErrorCode::ContextNotActive, "No Context"));
    CHECK(!fail_void.has_value());
    CHECK(fail_void.error().code == glpp::ErrorCode::ContextNotActive);
    CHECK(fail_void.error().message == "No Context");

    return g_failures == 0 ? 0 : 1;
}