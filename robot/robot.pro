TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    robot_git/src/main.c \
    robot_git/src/robot.c

HEADERS += \
    robot_git/src/robot.h

DISTFILES += \
    robot_git/src/input.txt
