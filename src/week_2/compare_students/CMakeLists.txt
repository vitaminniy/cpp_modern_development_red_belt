project(compare_students)

add_executable(${PROJECT_NAME} sort_students.cpp)
target_link_libraries(${PROJECT_NAME} test_runner)
target_link_libraries(${PROJECT_NAME} profile)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
