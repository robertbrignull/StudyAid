TEMPLATE = app
INCLUDEPATH += . src /usr/include/mysql /usr/include/mysql++
CONFIG += qt
QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -g

LIBS += -lmysqlpp -lmysqlclient

HEADERS += src/*.h src/pages/*.h src/database/*.h src/widgets/*.h
SOURCES += src/*.cpp src/pages/*.cpp src/database/*.cpp src/widgets/*.cpp

DESTDIR = .
OBJECTS_DIR = obj
MOC_DIR = moc
