QT += core gui widgets

TARGET = MooDooGUI
TEMPLATE = app

# Source files
SOURCES += \
    src/main_gui.cpp \
    src/MainWindow.cpp \
    src/Storage.cpp \
    src/AddTaskDialog.cpp \
    src/MoodEntryDialog.cpp \
    src/MoodHistoryPage.cpp \
    src/TaskListPage.cpp

# Header files
HEADERS += \
    src/MainWindow.h \
    src/AddTaskDialog.h \
    src/MoodEntryDialog.h \
    src/MoodHistoryPage.h \
    src/TaskListPage.h

# Include directories
INCLUDEPATH += src/

# C++ standard
CONFIG += c++17

# Build configuration
CONFIG(debug, debug|release) {
    TARGET = MooDooGUI_debug
} 