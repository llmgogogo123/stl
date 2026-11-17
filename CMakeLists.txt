cmake_minimum_required(VERSION 3.16)
project(mini_stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(mini_stl INTERFACE)
target_include_directories(mini_stl INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(MINI_STL_SANITIZE "Build tests with ASan/UBSan" ON)

enable_testing()

set(MINI_TESTS
    smoke
    grow_test
    count_test
    copy_move_test
    interface_test
    hash_smoke
    hash_insert_test
    hash_rehash_test
    hash_erase_test
    hash_fuzz_test
    hash_string_test
    vector_fuzz_test
)

foreach(test_name IN LISTS MINI_TESTS)
    add_executable(${test_name} tests/${test_name}.cpp)
    target_link_libraries(${test_name} PRIVATE mini_stl)
    target_compile_options(${test_name} PRIVATE -Wall -Wextra)

    if(MINI_STL_SANITIZE)
        target_compile_options(${test_name} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(${test_name} PRIVATE
            -fsanitize=address,undefined
        )
    endif()

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

add_executable(bench_map bench/bench_map.cpp)
target_link_libraries(bench_map PRIVATE mini_stl)
target_compile_options(bench_map PRIVATE -O2 -DNDEBUG -Wall -Wextra)

add_executable(pool_bench bench/pool.cpp)
target_link_libraries(pool_bench PRIVATE mini_stl)
target_compile_options(pool_bench PRIVATE -O2 -DNDEBUG -Wall -Wextra)