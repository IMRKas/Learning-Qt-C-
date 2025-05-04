TEMPLATE = app
CONFIG += c++17 console
QT += sql core gui widgets
INCLUDEPATH =+ include
SOURCES += src/main.cpp \
		   src/mainWindow.cpp \
		   src/taskForm.cpp

HEADERS += include/MainWindow.h \
		   include/TaskForm.h
