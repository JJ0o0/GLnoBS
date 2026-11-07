add_executable(header_check header_check.cpp)
target_link_libraries(header_check PRIVATE glpp::glpp)
add_test(NAME header_check COMMAND header_check)

add_executable(error_test diagnostics/error_test.cpp)
target_link_libraries(error_test PRIVATE glpp::glpp)
target_include_directories(error_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME error_test COMMAND error_test)

add_executable(result_test diagnostics/result_test.cpp)
target_link_libraries(result_test PRIVATE glpp::glpp)
target_include_directories(result_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME result_test COMMAND result_test)