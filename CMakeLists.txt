cmake_minimum_required(VERSION 3.16)

project(Student-course-selection-system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Student-course-selection-system main.cpp
    student.h student.cpp
    teacher.h teacher.cpp
    course.h course.cpp
    README.md
    system.h system.cpp
)


find_package(SQLite3 REQUIRED)
target_link_libraries(Student-course-selection-system PRIVATE SQLite::SQLite3)

include(GNUInstallDirs)
install(TARGETS Student-course-selection-system
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
