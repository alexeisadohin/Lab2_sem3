cmake_minimum_required(VERSION 3.28)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab2
        main.cpp
        Tests.cpp
        Student.cpp
)

target_include_directories(lab2 PUBLIC
        Sorts
        Sequences
        PTRs
)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

target_link_libraries(lab2 PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
