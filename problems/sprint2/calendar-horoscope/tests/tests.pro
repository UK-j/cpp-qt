########
MOCK_LIB=../../../../mocks_library
########

QT += testlib
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

isEmpty(MOCK_LIB) {
    MOCK_LIB=/tmp/practicum-qt-mocks
}

CONFIG += c++17

SUBMISSION_PATH = ../submission

INCLUDEPATH += $$SUBMISSION_PATH
INCLUDEPATH += $$MOCK_LIB

TEMPLATE = app

SOURCES +=  tests.cpp \
    $$SUBMISSION_PATH/magic_horoscope.cpp \
    $$SUBMISSION_PATH/mainwindow.cpp
    $$SUBMISSION_PATH/main.cpp

HEADERS +=  \
    $$SUBMISSION_PATH/magic_horoscope.h \
    $$SUBMISSION_PATH/mainwindow.h \
    $$MOCK_LIBRARY/test_utils/practicum_assert.hpp

FORMS += \
    $$SUBMISSION_PATH/mainwindow.ui
