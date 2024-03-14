cmake_minimum_required(VERSION 3.5)

project(strategie VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        commonActions.h
        constants.h
        context.h
        strategies.h
        robotActions.h
        mainwindow.h
        mainwindow.ui
        ui/gameElements/plants.cpp
        ui/gameElements/plants.h
        ../VRAC_sdk/include/JSON_overlay/jsonstatemachine.h
        ../VRAC_sdk/include/path_finding/path_finder.h
        ../VRAC_sdk/include/path_finding/path_checker.h
        ../VRAC_sdk/include/path_finding/path_planner.h
        ../VRAC_sdk/include/path_finding/path_step.h
        ../VRAC_sdk/include/qt_graphics_models/game_element.h
        ../VRAC_sdk/include/qt_graphics_models/obstacle.h
        ../VRAC_sdk/include/qt_graphics_models/playground.h
        ../VRAC_sdk/include/qt_graphics_models/robot.h
        ../VRAC_sdk/include/strategy/strategymanager.h
        ../VRAC_sdk/include/strategy/STM/event.h
        ../VRAC_sdk/include/strategy/STM/state.h
        ../VRAC_sdk/include/strategy/STM/stm.h
        ../VRAC_sdk/include/strategy/STM/transition.h

)


include_directories("../VRAC_SDK/libs/fmt")
include_directories("../VRAC_SDK/libs/nlohmann-json")
include_directories("../VRAC_SDK/libs/range-v3")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    add_compile_definitions(IS_RASPBERRY_PI)

endif()

qt6_add_resources("./ressources.qrc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(strategie
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET strategie APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(strategie SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(strategie
            ${PROJECT_SOURCES}
        )
    endif()
endif()



target_include_directories(strategie PUBLIC
    ../VRAC_sdk/include
    ../VRAC_sdk/libs
    ../VRAC_sdk/libs/nlohmann-json/include
    ../VRAC_sdk/libs/fmt/include
    ../VRAC_sdk/libs/range-v3/include
)

target_link_libraries(strategie PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.strategie)
endif()
set_target_properties(strategie PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS strategie
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(strategie)
endif()
