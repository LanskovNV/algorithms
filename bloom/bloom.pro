TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    bloom.c \
    test.c

HEADERS += \
    bloom.h \
    test.h

DISTFILES += \
    check.txt \
    load.txt
