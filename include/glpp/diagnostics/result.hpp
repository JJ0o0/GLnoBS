#pragma once

#include <glpp/diagnostics/error.hpp>
#include <cstdlib>
#include <utility>
#include <variant>

namespace glpp {
    template<typename T>
    class [[nodiscard("Result may hold an error; check has_value()")]] Result {
        public:
            Result(T value) : m_data(std::move(value)) {}
            Result(Error error) : m_data(std::move(error)) {}

            bool has_value() const {
                return std::holds_alternative<T>(m_data);
            }

            T& value() {
                if (!has_value()) {
                    std::abort();
                }
                
                return std::get<T>(m_data);
            }

            const T& value() const {
                if (!has_value()) {
                    std::abort();
                }

                return std::get<T>(m_data);
            }

            const Error& error() const {
                if (!std::holds_alternative<Error>(m_data)) {
                    std::abort();
                }

                return std::get<Error>(m_data);
            }
        private:
            std::variant<T, Error> m_data;
    };

    template<>
    class [[nodiscard("Result may hold an error; check has_value()")]] Result<void> {
        public:
            static Result success() { return Result(); }
            Result(Error error) : m_data(std::move(error)) {}

            bool has_value() const {
                return std::holds_alternative<std::monostate>(m_data);
            }

            const Error& error() const {
                if (!std::holds_alternative<Error>(m_data)) {
                    std::abort();
                }

                return std::get<Error>(m_data);
            }
        private:
            Result() = default;
            std::variant<std::monostate, Error> m_data;
    };
}