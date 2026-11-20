function(glpp_add_test name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE glpp::glpp)
    target_include_directories(${name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${name} PRIVATE -Wall -Wextra)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

glpp_add_test(header_check header_check.cpp)

glpp_add_test(error_test   diagnostics/error_test.cpp)
glpp_add_test(result_test  diagnostics/result_test.cpp)
glpp_add_test(log_test     diagnostics/log_test.cpp)

glpp_add_test(device_test  core/device_test.cpp)

find_package(glfw3)
if (glfw3_FOUND)
    glpp_add_test(device_gl_test core/device_gl_test.cpp)
    target_link_libraries(device_gl_test PRIVATE glad::glad glfw)
endif()