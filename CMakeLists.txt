cmake_minimum_required(VERSION 3.0)
project(MyProject)  # 设置项目名称

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 自动收集所有在 lib 文件夹下的源文件
file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/lib/*.cpp")

# 添加一个可执行文件
add_executable(MyExecutable ${SOURCE_FILES})
