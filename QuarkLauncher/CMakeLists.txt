cmake_minimum_required(VERSION 3.5)

project(QuarkLauncher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES QuarkLauncher_el_GR.ts)

set(PROJECT_SOURCES
        main.cpp
        quarklauncher.h
        quarklauncher.cpp
        quarklauncher.ui
        envvariables.h
        envvariables.cpp
        envvariables.ui
        utils/ansiescapecodehandler.cpp
        utils/ansiescapecodehandler.h
        console.h
        console.cpp
        console.ui
        widgets/quarkenv.h
        widgets/quarkenv.cpp
        widgets/quarkgroup.h
        widgets/quarkgroup.cpp
        widgets/quarkoption.h
        widgets/quarkoption.cpp
        widgets/quarkcontainer_widget.h
        widgets/quarkcontainer_widget.cpp
        widgets/quarkcontainer_groupbox.h
        widgets/quarkcontainer_groupbox.cpp
        widgets/quarkcheckbox.cpp
        widgets/quarkgroupbox.h
        widgets/quarkgroupbox.cpp
        widgets/quarkcheckbox.h
        widgets/quarkcheckbox.cpp
        widgets/quarklineedit.h
        widgets/quarklineedit.cpp
        widgets/quarkpathedit.h
        widgets/quarkpathedit.cpp
        widgets/quarkpathedit.ui
        resources/resources.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QuarkLauncher
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QuarkLauncher APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QuarkLauncher SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QuarkLauncher
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(QuarkLauncher PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QuarkLauncher PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QuarkLauncher)
endif()

set_target_properties(QuarkLauncher PROPERTIES OUTPUT_NAME "quarkle")

install(TARGETS QuarkLauncher)