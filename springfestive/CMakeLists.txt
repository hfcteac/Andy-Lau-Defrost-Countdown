cmake_minimum_required(VERSION 3.16)

project(project1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

set(PROJECT_SOURCES
    main.cpp
    widget.cpp
    widget.h
)

qt_add_executable(project1
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(project1 PRIVATE
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
)

set_target_properties(project1 PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS project1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(project1)
