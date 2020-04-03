TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    sum.c

HEADERS += \
    sum.h

DISTFILES += \
    input.txt \
    output.txt \
    no_sum.txt \
    no_elements.txt \
    all_bigger_than_sum.txt \
    test.txt
