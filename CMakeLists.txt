
cmake_minimum_required(VERSION 3.10)
project(libuv-test)

set(CMAKE_CXX_STANDARD 11)

set(LIBUV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/libuv-v1.9.1/")
set(LIBUV_LIB "${LIBUV_DIR}/out/Debug/libuv.a")

include_directories(${LIBUV_DIR}/include)


add_executable(hello src/command/hello.cc)
target_link_libraries(hello ${LIBUV_LIB})

add_executable(idle_handle src/command/idle_handle.cc)
target_link_libraries(idle_handle ${LIBUV_LIB})

add_executable(swap_child_process src/command/swap_child_process.cc)
target_link_libraries(swap_child_process ${LIBUV_LIB})