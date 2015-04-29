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
    termbucket.cpp \
    porter2_stemmer.cpp \
    pageinfo.cpp \
    aprnsatpage.cpp \
    avltreeindex.cpp \
    avltreeinterface.cpp \
    docparser.cpp \
    indexhandler.cpp \
    queryprocessor.cpp


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    indexinterface.h \
    hashtableindex.h \
    letterterms.h \
    term.h \
    termbucket.h \
    porter2_stemmer.h \
    pageinfo.h \
    aprnsatpage.h \
    avltreeindex.h \
    avltreeinterface.h \
    docparser.h \
    indexhandler.h \
    queryprocessor.h

