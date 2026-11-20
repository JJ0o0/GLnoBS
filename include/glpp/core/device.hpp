#pragma once

#include <glpp/diagnostics/result.hpp>

namespace glpp {
    class Device {
        public:
            static Result<Device> create();
        private:
            Device() = default;
    };
}