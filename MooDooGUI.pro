QT += core gui widgets

TARGET = MooDooGUI
TEMPLATE = app

# Source files
SOURCES += \
    src/main_gui.cpp \
    src/MainWindow.cpp

# Header files
HEADERS += \
    src/MainWindow.h

# Include directories
INCLUDEPATH += src/

# C++ standard
CONFIG += c++17

# Build configuration
CONFIG(debug, debug|release) {
    TARGET = MooDooGUI_debug
} 