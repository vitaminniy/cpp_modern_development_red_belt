project(profile)

add_library(${PROJECT_NAME} profile.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
