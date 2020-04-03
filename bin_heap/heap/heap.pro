TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../bin_heap_git/heap.c \
    ../bin_heap_git/main.c \
    ../bin_heap_git/test.c

HEADERS += \
    ../bin_heap_git/heap.h \
    ../bin_heap_git/test.h

DISTFILES += \
    ../bin_heap_git/load.txt
