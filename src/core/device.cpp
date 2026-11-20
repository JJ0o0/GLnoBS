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

        return Device();
    }
}