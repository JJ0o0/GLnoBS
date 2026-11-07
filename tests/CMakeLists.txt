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