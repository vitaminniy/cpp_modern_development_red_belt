project(paginator)

add_executable(${PROJECT_NAME} paginator.cpp)
target_link_libraries(${PROJECT_NAME} test_runner)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
