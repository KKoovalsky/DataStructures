cmake_minimum_required(VERSION 3.5)

project(test_cdata_structs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(TEST_DIR ${ROOT_DIR}/tests)
set(PRJ_NAME ${CMAKE_PROJECT_NAME})

add_definitions(-DSNOW_ENABLED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

file(GLOB SRC_FILES ${TEST_DIR}/*.c)

include_directories(${ROOT_DIR} ${TEST_DIR}/snow)

add_executable(${PRJ_NAME} ${SRC_FILES})

add_custom_target(run-test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${PRJ_NAME}
)
