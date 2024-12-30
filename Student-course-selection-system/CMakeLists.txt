cmake_minimum_required(VERSION 3.16)

project(Student-course-selection-system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Student-course-selection-system main.cpp
    course.h
    system.h system.cpp)

include(GNUInstallDirs)
install(TARGETS Student-course-selection-system
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
