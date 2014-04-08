TEMPLATE = app
INCLUDEPATH += . src /usr/include/mysql /usr/include/mysql++
CONFIG += qt testcase
QT += widgets testlib

QMAKE_CXXFLAGS += -std=c++11 -g -Wall -Wextra -Werror

LIBS += -lmysqlpp -lmysqlclient

RESOURCES = resources.qrc

HEADERS += src/*.h src/pages/*.h src/database/*.h src/widgets/*.h src/forms/*.h src/latex/*.h src/test/*.h src/views/*.h
SOURCES += src/*.cpp src/pages/*.cpp src/database/*.cpp src/widgets/*.cpp src/forms/*.cpp src/latex/*.cpp src/test/*.cpp src/views/*.cpp

DESTDIR = .
OBJECTS_DIR = obj
MOC_DIR = moc
