cmake_minimum_required(VERSION 3.13)
project(SO2_P2)

#set(CURSES_NEED_NCURSES TRUE)
#find_package(Curses REQUIRED)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread -lncurses")
find_package(Threads)

add_executable(SO2_P2 main.cpp)
#target_link_libraries(pro2 ${CURSES_LIBRARIES})
#target_link_libraries(pro2 ${CMAKE_THREAD_LIBS_INIT})