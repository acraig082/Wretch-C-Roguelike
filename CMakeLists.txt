# CMakeLists.txt
cmake_minimum_required(VERSION 3.6)   # CMake version check
project(FinalProject)

set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

set(SOURCE_FILES main.c level.c room.c player.c userInterface.c enemy.c combat.c PriorityQueue.c armor.c inventory.c item.c scroll.c weapon.c node.c roll.c potion.c)

add_executable(FinalProject ${SOURCE_FILES})
target_link_libraries(FinalProject ${CURSES_LIBRARIES})
