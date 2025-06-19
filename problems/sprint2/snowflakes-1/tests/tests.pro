########
MOCK_LIB=../../../../mocks_library
########

QT += testlib
QT += gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

CONFIG += c++17

isEmpty(MOCK_LIB) {
    MOCK_LIB=/tmp/practicum-qt-mocks
}

DEFINES += "PRAC_TESTS"

SUBMISSION_PATH = ../submission

INCLUDEPATH += $$SUBMISSION_PATH
INCLUDEPATH += $$MOCK_LIB

TEMPLATE = app

SOURCES += \
    tests.cpp \
    $$SUBMISSION_PATH/winterwindow.cpp

HEADERS +=  \
    $$SUBMISSION_PATH/winterwindow.h\
    $$MOCK_LIB/prac/QPainter

FORMS += \
    $$SUBMISSION_PATH/winterwindow.ui

