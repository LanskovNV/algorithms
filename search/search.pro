TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    search.c

HEADERS += \
    search.h

DISTFILES += \
    input.txt \
    memtest.txt \
    line.txt \
    solo.txt \
    alone.txt \
    empty_graph.txt \
    test.txt
