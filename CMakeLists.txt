cmake_minimum_required(VERSION 3.14)

project(qml-clipboard-manager LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Quick REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        clipboardmodel.h
        clipboardmodel.cpp
        clipboardmanager.h
        clipboardmanager.cpp
        imageutils.h
        imageutils.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qml-clipboard-manager
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(qml-clipboard-manager SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(qml-clipboard-manager
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(qml-clipboard-manager
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qml-clipboard-manager
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Quick)
