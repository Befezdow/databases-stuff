TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ui-menu.cpp \
    db-service.cpp \
    contact.cpp \
    email.cpp \
    number.cpp

HEADERS += \
    ui-menu.h \
    db-service.h \
    contact.h \
    email.h \
    number.h
