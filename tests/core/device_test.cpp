#include "check.hpp"
#include <glpp/glpp.hpp>

int main() {
    auto result = glpp::Device::create();
    CHECK(!result.has_value());
    CHECK(result.error().code == glpp::ErrorCode::LoaderNotInitialized);
    return g_failures == 0 ? 0 : 1;
}