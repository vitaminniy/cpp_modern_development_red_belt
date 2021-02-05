project(ebook)

add_executable(${PROJECT_NAME} slow.cpp)

file(COPY ${PROJECT_SOURCE_DIR}/input.txt
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
