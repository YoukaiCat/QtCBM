QT += core gui charts

QT += widgets

CONFIG += c++1z

QMAKE_CXXFLAGS += -std=c++17

TARGET = QtCBM
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS \
    QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
        src/main.cpp \
        src/MainWindow.cpp \
        src/Dot.cpp \
        src/DotLabel.cpp \
        src/Stimul.cpp \
        src/TextStimul.cpp \
        src/Cross.cpp \
        src/CrossLabel.cpp \
        src/DotProbe.cpp \
        src/ProbeResult.cpp \
        src/DotProber.cpp

HEADERS += \
        src/MainWindow.h \
        src/Dot.h \
        src/DotLabel.h \
        src/Stimul.h \
        src/TextStimul.h \
        src/Cross.h \
        src/CrossLabel.h \
        src/DotProbePhase.h \
        src/DotProbe.h \
        src/ProbeResult.h \
        src/DotProber.h \
        src/LayoutMode.h

FORMS += \
        src/MainWindow.ui
