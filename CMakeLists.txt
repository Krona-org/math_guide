cmake_minimum_required(VERSION 3.21...3.30)

project(math_guide LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(APP_RESOURCES
    resourses.qrc
)

file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.hpp
    src/*.h
)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui Qml Quick)

qt_standard_project_setup()

qt_add_executable(math_guide ${APP_SOURCES} ${APP_RESOURCES})

target_include_directories(math_guide PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/test001_autogen/include
    ${CMAKE_CURRENT_BINARY_DIR}/test001_autogen/include_Debug   # для Debug конфигурации
)

target_link_libraries(math_guide PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

set_target_properties(math_guide PROPERTIES
    WIN32_EXECUTABLE TRUE
)