cmake_minimum_required(VERSION 3.16)
project(HW3_2_)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW3_2_ Main_Interface.cpp Users/Table_of_users.h "Access level/red_level.h" "Access level/yellow_level.h" "Access level/green_level.h" "Access level/blue_level.h" "Access level/no_level.h" Users/user.h)