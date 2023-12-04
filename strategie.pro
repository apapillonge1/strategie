QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    utility.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    ressources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#IUT CONFIG

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/release/ -lVRAC_eurobot_sdk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/debug/ -lVRAC_eurobot_sdk
else:unix: LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_6_0_MinGW_64_bit-Debug/ -lVRAC_eurobot_sdk

INCLUDEPATH += $$PWD/../VRAC_sdk
DEPENDPATH += $$PWD/../VRAC_sdk

#Antonin Config


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/release/ -lVRAC_eurobot_sdk
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/debug/ -lVRAC_eurobot_sdk
#else:unix: LIBS += -L$$PWD/../build-VRAC_eurobot_sdk-Desktop_Qt_6_3_2_MinGW_64_bit-Debug/ -lVRAC_eurobot_sdk

#INCLUDEPATH += $$PWD/../VRAC_sdk
#DEPENDPATH += $$PWD/../VRAC_sdk
