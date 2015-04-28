TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

SOURCES += main.cpp \
    indexinterface.cpp \
    hashtableindex.cpp \
    letterterms.cpp \
    term.cpp \
    aprnsatdoc.cpp \
    termbucket.cpp \
    porter2_stemmer.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    indexinterface.h \
    hashtableindex.h \
    letterterms.h \
    term.h \
    aprnsatdoc.h \
    termbucket.h \
    porter2_stemmer.h

