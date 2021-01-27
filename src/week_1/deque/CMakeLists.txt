project(deque)

add_library(${PROJECT_NAME} deque.cpp)

enable_testing()

add_executable(${PROJECT_NAME}_test deque_test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_test test_runner)

add_test(${PROJECT_NAME} ${PROJECT_NAME}_test)
