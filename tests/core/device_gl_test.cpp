#include "check.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glpp/glpp.hpp>

#include <iostream>

namespace {
    void glfw_error_callback(int code, const char* description) {
        std::cerr << "GLFW Error " << code << ": " << description << "\n";
    }
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);

    if (glfwInit() == GLFW_FALSE) {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* glfw_window = glfwCreateWindow(
        64, 64,
        "glpp test",
        nullptr, nullptr
    );

    if (glfw_window == nullptr) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(glfw_window);

    int version = gladLoadGL(glfwGetProcAddress);
    CHECK(version != 0);

    int major = GLAD_VERSION_MAJOR(version);
    int minor = GLAD_VERSION_MINOR(version);
    CHECK(major > 3 || (major == 3 && minor >= 3));

    auto device = glpp::Device::create();
    CHECK(device.has_value());

    glfwMakeContextCurrent(nullptr);
        auto no_context = glpp::Device::create();
        CHECK(!no_context.has_value() && no_context.error().code == glpp::ErrorCode::ContextNotActive);
    glfwMakeContextCurrent(glfw_window);

    glfwDestroyWindow(glfw_window);
    glfwTerminate();

    return g_failures == 0 ? 0 : 1;
}