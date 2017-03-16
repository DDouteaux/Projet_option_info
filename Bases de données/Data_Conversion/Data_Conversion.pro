TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    jsonworker.cpp \
    amazonworker.cpp \
    rottenworker.cpp \
    largemovieworker.cpp \
    twitterworker.cpp \
    umichworker.cpp \
    sentimentworker.cpp

HEADERS += \
    jsonworker.h \
    amazonworker.h \
    rottenworker.h \
    largemovieworker.h \
    twitterworker.h \
    umichworker.h \
    sentimentworker.h

