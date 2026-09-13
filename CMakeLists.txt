cmake_minimum_required(VERSION 3.21)
project(audio_player LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# miniaudio compiled exactly once, as its own target
add_library(miniaudio STATIC src/miniaudio_impl.cpp)
target_include_directories(miniaudio PUBLIC third_party)
find_package(Threads REQUIRED)
target_link_libraries(miniaudio PUBLIC Threads::Threads ${CMAKE_DL_LIBS})
if(MSVC)
  target_compile_options(miniaudio PRIVATE /w)   # silence third-party warnings
endif()

add_executable(audioplayer src/main.cpp src/Decoder.cpp)
target_link_libraries(audioplayer PRIVATE miniaudio)
if(MSVC)
  target_compile_options(audioplayer PRIVATE /W4 /permissive- /utf-8)
else()
  target_compile_options(audioplayer PRIVATE -Wall -Wextra -Wpedantic)
endif()