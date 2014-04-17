# Note this project needs mysql and libxml++-2.6 installed

TEMPLATE = app
INCLUDEPATH += . src /usr/include/mysql /usr/include/mysql++ /usr/include/libxml2 /usr/include/glibmm-2.4 /usr/lib/x86_64-linux-gnu/glibmm-2.4/include /usr/include/sigc++-2.0 /usr/lib/x86_64-linux-gnu/sigc++-2.0/include /usr/include/glib-2.0 /usr/lib/x86_64-linux-gnu/glib-2.0/include /usr/include/libxml++-2.6 /usr/lib/libxml++-2.6/include
CONFIG += qt testcase
QT += widgets testlib

QMAKE_CXXFLAGS += -std=c++11 -g -Wall -Wextra -Werror

LIBS += -lmysqlpp -lmysqlclient -lxml++-2.6 -lxml2 -lglibmm-2.4 -lgobject-2.0 -lsigc-2.0 -lglib-2.0

RESOURCES = resources.qrc

HEADERS += src/*.h src/pages/*.h src/database/*.h src/widgets/*.h src/forms/*.h src/latex/*.h src/test/*.h src/views/*.h
SOURCES += src/*.cpp src/pages/*.cpp src/database/*.cpp src/widgets/*.cpp src/forms/*.cpp src/latex/*.cpp src/test/*.cpp src/views/*.cpp

DESTDIR = .
OBJECTS_DIR = obj
MOC_DIR = moc
