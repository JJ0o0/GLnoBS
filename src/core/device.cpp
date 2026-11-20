#include <glpp/core/device.hpp>
#include <glad/gl.h>

namespace glpp {
    Result<Device> Device::create() {
        if (glGetString == nullptr) {
            return Error(
                ErrorCode::LoaderNotInitialized, 
                "Device::create() failed: the OpenGL loader is not initialized. Call your loader (e.g. gladLoadGL) with a current context before creating a Device."
            );
        }

        /*
            Best effort: calling glGetString without a current context is undefined behaviour per the OpenGL spec.
            Most drivers return nullptr, which is what this check relies on, but some may crash instead.
        */
        if (glGetString(GL_VERSION) == nullptr) {
            return Error(
                ErrorCode::ContextNotActive,
                "Device::create() failed: there isn't any OpenGL context in this thread. Before creating a Device, make a context current (e.g. glfwMakeContextCurrent)."
            );
        }

        return Device();
    }
}