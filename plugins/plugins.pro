include(../qtreetabs.pri)

# Build a plugin for QDesigner
QT += uiplugin
CONFIG += plugin
TEMPLATE = lib
TARGET = qtreetabsplugin
LIBS += ../src/libqtreetabs.a

# Define the sources that are needed
SOURCES += qtreetabsdesignerplugin.cpp
HEADERS += qtreetabsdesignerplugin.h

# Define the installation path
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target
