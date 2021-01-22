project(bad_macro)

add_executable(${PROJECT_NAME} bad_macro.cpp)
target_link_libraries(${PROJECT_NAME} test_runner)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
