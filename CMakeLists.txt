cmake_minimum_required(VERSION 3.20)
project(e1rm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(e1rm main.cpp)
target_compile_options(e1rm PRIVATE -Wall -Wextra -Wpedantic)

# Lets snapcraft's cmake plugin find the binary: with
# CMAKE_INSTALL_PREFIX=/usr it lands in usr/bin/e1rm inside the snap.
install(TARGETS e1rm RUNTIME DESTINATION bin)
