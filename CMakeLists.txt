cmake_minimum_required(VERSION 3.16)
project(ds_demo LANGUAGES CXX)

# MSVC 用最新标准，其余统一 C++23
if(MSVC)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_STANDARD_REQUIRED ON)
    add_compile_options(/std:c++23preview)
else()
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# 统一输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 主程序
file(GLOB_RECURSE SRC_LIST "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(ds_main ${SRC_LIST})
target_include_directories(ds_main PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)
if(MINGW)
    target_link_options(ds_main PRIVATE -mconsole)
endif()
if(MSVC)
    target_compile_options(ds_main PRIVATE
        $<$<CONFIG:Release>:/MT>
        $<$<CONFIG:Debug>:/MTd>)
endif()

# 测试
file(GLOB TEST_SRCS "${CMAKE_SOURCE_DIR}/tests/test_*.cpp")
foreach(t ${TEST_SRCS})
    get_filename_component(name_we ${t} NAME_WE)
    add_executable(${name_we} ${t} ${SRC_LIST_NO_MAIN})
    target_include_directories(${name_we} PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
    )
endforeach()