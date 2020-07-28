project(i3status-kbd-layout)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(i3status-kbd-layout
  XKeyboard.cpp
  i3status_kbd_layout.cpp)

target_link_libraries(i3status-kbd-layout
  X11)
