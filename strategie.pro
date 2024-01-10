QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ui/gameElements/plants.cpp

HEADERS += \
    ../VRAC_sdk/include/JSON_overlay/jsonstatemachine.h \
    ../VRAC_sdk/include/obstacle_detection/detectionmanager.h \
    ../VRAC_sdk/include/obstacle_detection/detectionutilities.h \
    ../VRAC_sdk/include/obstacle_detection/sensor.h \
    ../VRAC_sdk/include/path_finding/path_checker.h \
    ../VRAC_sdk/include/path_finding/path_finder.h \
    ../VRAC_sdk/include/path_finding/path_planner.h \
    ../VRAC_sdk/include/path_finding/path_step.h \
    ../VRAC_sdk/include/qt_graphics_models/game_element.h \
    ../VRAC_sdk/include/qt_graphics_models/obstacle.h \
    ../VRAC_sdk/include/qt_graphics_models/playground.h \
    ../VRAC_sdk/include/qt_graphics_models/robot.h \
    ../VRAC_sdk/include/strategy/GOAP/action.hpp \
    ../VRAC_sdk/include/strategy/GOAP/goal.hpp \
    ../VRAC_sdk/include/strategy/GOAP/goap.hpp \
    ../VRAC_sdk/include/strategy/GOAP/planner.hpp \
    ../VRAC_sdk/include/strategy/GOAP/world_state.hpp \
    ../VRAC_sdk/include/strategy/STM/event.h \
    ../VRAC_sdk/include/strategy/STM/state.h \
    ../VRAC_sdk/include/strategy/STM/stm.h \
    ../VRAC_sdk/include/strategy/STM/transition.h \
    ../VRAC_sdk/include/strategy/strategymanager.h \
    constants.h \
    mainwindow.h \
    strategies.h \
    ui/gameElements/plants.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    ressources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += \
    ../VRAC_sdk/include \
    ../VRAC_sdk/libs \
    ../VRAC_sdk/libs/range-v3/include \
    ../VRAC_sdk/libs/nlohmann-json/include \
    ../VRAC_sdk/libs/fmt/include \


#IUT CONFIG

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/release/ -lVRAC_eurobot_sdk
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/debug/ -lVRAC_eurobot_sdk
#else:unix: LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/ -lVRAC_eurobot_sdk

#INCLUDEPATH += $$PWD/../VRAC_sdk
#DEPENDPATH += $$PWD/../VRAC_sdk

#Antonin Config


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/release/ -lVRAC_eurobot_sdk
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/debug/ -lVRAC_eurobot_sdk
#else:unix: LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/ -lVRAC_eurobot_sdk

#INCLUDEPATH += $$PWD/../VRAC_sdk
#DEPENDPATH += $$PWD/../VRAC_sdk
