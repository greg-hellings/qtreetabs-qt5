include(../qtreetabs.pri)

TEMPLATE = lib
TARGET = qtreetabs
HEADERS = opentab.h \
          qtreetabs.h \
          js/localscript.h
SOURCES = opentab.cpp \
          qtreetabs.cpp \
          js/localscript.cpp
RESOURCES = web/web.qrc \
            js/resources.qrc
FORMS = qtreetabs.ui
